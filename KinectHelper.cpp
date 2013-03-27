#include "KinectHelper.h"


KinectHelper::KinectHelper(void)
{
	m_zoomFactor = 1.0f;
	m_viewOffset.x = 0;
	m_viewOffset.y = 0;
	m_isFaceTracked = false;
	m_videoCameraConfig.Height = kinect_height;
	m_videoCameraConfig.Width = kinect_width;
	m_videoCameraConfig.FocalLength = NUI_CAMERA_COLOR_NOMINAL_FOCAL_LENGTH_IN_PIXELS;
	m_depthCameraConfig.Height = kinect_height;
	m_depthCameraConfig.Width = kinect_width;
	m_depthCameraConfig.FocalLength = NUI_CAMERA_DEPTH_NOMINAL_FOCAL_LENGTH_IN_PIXELS * 2.f;
}


KinectHelper::~KinectHelper(void)
{
	m_pFTResult->Release();
	m_videoBuffer->Release();
	m_drawBuffer->Release();
	m_depthBuffer->Release();
	m_pFT->Release();
}

HRESULT KinectHelper::initKinect(){
	HRESULT hr = E_UNEXPECTED;
	m_videoBuffer = FTCreateImage();
	if (!m_videoBuffer){
		return E_OUTOFMEMORY;
	}
	hr = m_videoBuffer->Allocate(kinect_width, kinect_height, FTIMAGEFORMAT_UINT8_B8G8R8X8);
	if (FAILED(hr)){
		return hr;
	}
	m_drawBuffer = FTCreateImage();
	if (!m_drawBuffer){
		return E_OUTOFMEMORY;
	}
	hr = m_drawBuffer->Allocate(kinect_width, kinect_height, FTIMAGEFORMAT_UINT8_B8G8R8X8);
	if (FAILED(hr)){
		return hr;
	}
	m_depthBuffer = FTCreateImage();
	if (!m_depthBuffer){
		return E_OUTOFMEMORY;
	}
	hr = m_depthBuffer->Allocate(kinect_width, kinect_height, FTIMAGEFORMAT_UINT16_D13P3);
	if (FAILED(hr)){
		return hr;
	}
	hr = NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH | NUI_INITIALIZE_FLAG_USES_COLOR);
	if(FAILED(hr)){
		return hr;
	}
	hr = NuiImageStreamOpen(
		NUI_IMAGE_TYPE_COLOR,            // Depth camera or rgb camera?
		NUI_IMAGE_RESOLUTION_640x480,    // Image resolution
		0,      // Image stream flags, e.g. near mode
		2,      // Number of frames to buffer
		NULL,   // Event handle
		&m_videoStream);
	if(FAILED(hr)){
		return hr;
	}
	hr = NuiImageStreamOpen(
		NUI_IMAGE_TYPE_DEPTH,
		NUI_IMAGE_RESOLUTION_640x480,
		NUI_IMAGE_STREAM_FLAG_ENABLE_NEAR_MODE,
		2,
		NULL,
		&m_depthStream);
	if(FAILED(hr)){
		return hr;
	}
	m_pFT = FTCreateFaceTracker();
	if(!m_pFT){
		// Handle errors
	}
	// Initialize the face tracker
	hr = m_pFT->Initialize(&m_videoCameraConfig, &m_depthCameraConfig, NULL, NULL);
	if(FAILED(hr)){
		return hr;
	}
	m_pFTResult = NULL;
	hr = m_pFT->CreateFTResult(&m_pFTResult);
	return hr;
}

void KinectHelper::getVideoFrame(){
	const NUI_IMAGE_FRAME* pImageFrame = NULL;
	NUI_LOCKED_RECT LockedRect;
	HRESULT hr = NuiImageStreamGetNextFrame(m_videoStream, 0, &pImageFrame);
	if(FAILED(hr)){
		return;
	}
	INuiFrameTexture* pTexture = pImageFrame->pFrameTexture;
	pTexture->LockRect(0, &LockedRect, NULL, 0);
	if (LockedRect.Pitch)
	{   // Copy video frame to face tracking
		memcpy(m_videoBuffer->GetBuffer(), PBYTE(LockedRect.pBits), std::min(m_videoBuffer->GetBufferSize(), UINT(pTexture->BufferLen())));
	}
	pTexture->UnlockRect(0);
	hr = NuiImageStreamReleaseFrame(m_videoStream, pImageFrame);
}

void KinectHelper::getDepthFrame(){
	const NUI_IMAGE_FRAME* pImageFrame = NULL;
	NUI_LOCKED_RECT LockedRect;
	HRESULT hr = NuiImageStreamGetNextFrame(m_depthStream, 0, &pImageFrame);
	if(FAILED(hr)){
		return;
	}
	INuiFrameTexture* pTexture = pImageFrame->pFrameTexture;
	pTexture->LockRect(0, &LockedRect, NULL, 0);
	if (LockedRect.Pitch)
	{   // Copy video frame to face tracking
		memcpy(m_depthBuffer->GetBuffer(), PBYTE(LockedRect.pBits), std::min(m_depthBuffer->GetBufferSize(), UINT(pTexture->BufferLen())));
	}
	pTexture->UnlockRect(0);
	hr = NuiImageStreamReleaseFrame(m_depthStream, pImageFrame);
}

cv::Mat KinectHelper::video2Mat(IFTImage* pBuffer){
	cv::Mat image(kinect_height, kinect_width, CV_8UC4, pBuffer->GetBuffer());
	return image;
}

cv::Mat KinectHelper::depth2Mat(IFTImage* pBuffer){
	cv::Mat image(kinect_height, kinect_width, CV_8UC4);
	const USHORT* curr = reinterpret_cast<const USHORT*>(pBuffer->GetBuffer());
	for(int y = 0; y < kinect_height; ++y){
		cv::Vec4b* rowPtr = image.ptr<cv::Vec4b>(y);
		for(int x = 0; x < kinect_width; ++x){
			USHORT depth = NuiDepthPixelToDepth(curr[y * kinect_width + x]);
			BYTE value = depth % 256;
			rowPtr[x] = cv::Vec4b(value, value, value, value);
		}
	}
	return image;
}

void KinectHelper::trackFace(){
	HRESULT hr = E_UNEXPECTED;
	FT_SENSOR_DATA sensorData(m_videoBuffer, m_depthBuffer, m_zoomFactor, &m_viewOffset);
	getVideoFrame();
	getDepthFrame();
	if(!m_isFaceTracked){
		// Initiate face tracking.
		// This call is more expensive and searches over the input RGB frame for a face.
		hr = m_pFT->StartTracking(&sensorData, NULL, NULL, m_pFTResult);
		if(SUCCEEDED(hr) && SUCCEEDED(m_pFTResult->GetStatus())){
			m_isFaceTracked = true;
		}
		else{
			m_isFaceTracked = false;
		}
	}
	else{
		// Continue tracking. It uses a previously known face position.
		// This call is less expensive than StartTracking()
		hr = m_pFT->ContinueTracking(&sensorData, NULL, m_pFTResult);
		if(FAILED(hr) || FAILED (m_pFTResult->GetStatus())){
			m_isFaceTracked = false;
		}
	}
}

void KinectHelper::processFaceModel(){
	FT_VECTOR2D* pFTVector2D;
	UINT pointCount;
	HRESULT hr = m_pFTResult->Get2DShapePoints(&pFTVector2D, &pointCount);
	m_landmarkPoints.clear();
	m_landmarkPoints.reserve(pointCount);
	for(UINT i = 0; i < pointCount; ++i){
		m_landmarkPoints.push_back(cv::Point2f(pFTVector2D[i].x, pFTVector2D[i].y));
	}
}

HRESULT KinectHelper::visualizeFaceModel(){
	HRESULT hr = m_videoBuffer->CopyTo(m_drawBuffer, NULL, 0, 0);
	IFTModel* pModel;
	m_pFT->GetFaceModel(&pModel);
	FLOAT* pSUCoef = NULL;
	UINT numSU;
	BOOL suConverged;
	m_pFT->GetShapeUnits(NULL, &pSUCoef, &numSU, &suConverged);
	UINT vertexCount = pModel->GetVertexCount();
	FT_VECTOR2D* pPts2D = reinterpret_cast<FT_VECTOR2D*>(_malloca(sizeof(FT_VECTOR2D) * vertexCount));
	if (pPts2D){
		FLOAT *pAUs;
		UINT auCount;
		hr = m_pFTResult->GetAUCoefficients(&pAUs, &auCount);
		if (SUCCEEDED(hr)){
			FLOAT scale, rotationXYZ[3], translationXYZ[3];
			hr = m_pFTResult->Get3DPose(&scale, rotationXYZ, translationXYZ);
			if (SUCCEEDED(hr)){
				hr = pModel->GetProjectedShape(&m_videoCameraConfig, m_zoomFactor, m_viewOffset, pSUCoef, pModel->GetSUCount(), pAUs, auCount, 
					scale, rotationXYZ, translationXYZ, pPts2D, vertexCount);
				if (SUCCEEDED(hr)){
					POINT* p3DMdl   = reinterpret_cast<POINT*>(_malloca(sizeof(POINT) * vertexCount));
					if (p3DMdl){
						for (UINT i = 0; i < vertexCount; ++i){
							p3DMdl[i].x = LONG(pPts2D[i].x + 0.5f);
							p3DMdl[i].y = LONG(pPts2D[i].y + 0.5f);
						}
						FT_TRIANGLE* pTriangles;
						UINT triangleCount;
						hr = pModel->GetTriangles(&pTriangles, &triangleCount);
						if (SUCCEEDED(hr)){
							struct EdgeHashTable{
								UINT32* pEdges;
								UINT edgesAlloc;
								void Insert(int a, int b){
									UINT32 v = (std::min(a, b) << 16) | std::max(a, b);
									UINT32 index = (v + (v << 8)) * 49157, i;
									for (i = 0; i < edgesAlloc - 1 && pEdges[(index + i) & (edgesAlloc - 1)] && v != pEdges[(index + i) & (edgesAlloc - 1)]; ++i){
									}
									pEdges[(index + i) & (edgesAlloc - 1)] = v;
								}
							} eht;

							eht.edgesAlloc = 1 << UINT(log(2.f * (1 + vertexCount + triangleCount)) / log(2.f));
							eht.pEdges = reinterpret_cast<UINT32*>(_malloca(sizeof(UINT32) * eht.edgesAlloc));
							if (eht.pEdges)
							{
								ZeroMemory(eht.pEdges, sizeof(UINT32) * eht.edgesAlloc);
								for (UINT i = 0; i < triangleCount; ++i)
								{ 
									eht.Insert(pTriangles[i].i, pTriangles[i].j);
									eht.Insert(pTriangles[i].j, pTriangles[i].k);
									eht.Insert(pTriangles[i].k, pTriangles[i].i);
								}
								for (UINT i = 0; i < eht.edgesAlloc; ++i)
								{
									if(eht.pEdges[i] != 0)
									{
										m_drawBuffer->DrawLine(p3DMdl[eht.pEdges[i] >> 16], p3DMdl[eht.pEdges[i] & 0xFFFF], 0x00FFFF00, 1);
									}
								}
								_freea(eht.pEdges);
							}

							// Render the face rect in magenta
							RECT rectFace;
							hr = m_pFTResult->GetFaceRect(&rectFace);
							if (SUCCEEDED(hr))
							{
								POINT leftTop = {rectFace.left, rectFace.top};
								POINT rightTop = {rectFace.right - 1, rectFace.top};
								POINT leftBottom = {rectFace.left, rectFace.bottom - 1};
								POINT rightBottom = {rectFace.right - 1, rectFace.bottom - 1};
								UINT32 nColor = 0xff00ff;
								SUCCEEDED(hr = m_drawBuffer->DrawLine(leftTop, rightTop, nColor, 1)) &&
									SUCCEEDED(hr = m_drawBuffer->DrawLine(rightTop, rightBottom, nColor, 1)) &&
									SUCCEEDED(hr = m_drawBuffer->DrawLine(rightBottom, leftBottom, nColor, 1)) &&
									SUCCEEDED(hr = m_drawBuffer->DrawLine(leftBottom, leftTop, nColor, 1));
							}
						}

						_freea(p3DMdl); 
					}
					else{
						hr = E_OUTOFMEMORY;
					}
				}
			}
		}
		_freea(pPts2D);
	}
	else{
		hr = E_OUTOFMEMORY;
	}
	return hr;
}

std::vector<float> KinectHelper::getAUCoefficients(){
	FLOAT *p_coefficients;
	UINT count;
	m_pFTResult->GetAUCoefficients(&p_coefficients, &count);
	std::vector<float> array(p_coefficients, p_coefficients + count);
	return array;
}