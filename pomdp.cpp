#include "pomdp.h"


pomdp::pomdp(void)
{
}



pomdp::~pomdp(void)
{
}

void pomdp::init(){
	state s;
	m_states.push_back(s); m_states.push_back(s);
	action a;
	m_actions.push_back(a); m_actions.push_back(a);
	expand(3);
}

void pomdp::expand(int g){
	std::default_random_engine engine;
	std::uniform_real_distribution<float> gen(0.f, 1.f);
	int state_count = static_cast<int>(m_states.size());
	m_belief_points.clear();
	m_belief_points.reserve(g);
	for(int i = 0; i < g; ++i){
		point p(state_count);
		for(int j = 0; j < state_count; ++j){
			p.data[j] = gen(engine);
		}
		p.l1_normalize();
		m_belief_points.push_back(p);
	}
}

void pomdp::backup(){
	//int state_count = static_cast<int>(m_states.size());
	//boost::unordered_map<std::tuple<int, int>, point> gamma_set;
	//for(size_t i = 0; i < m_actions.size(); ++i){
	//	for(size_t j = 0; j < m_observations.size(); ++j){
	//		point alpha_a_z(state_count);
	//		for(size_t k = 0; k < m_gamma_set.size(); ++k){
	//			for(int s = 0; s < state_count; ++s){
	//				alpha_a_z.data[s] = 0.f;
	//				for(int s_p = 0; s_p <state_count; ++s_p){
	//					alpha_a_z.data[s] += m_transition_map[std::tuple<int, int, int>(m_states[s], m_actions[i], m_states[s_p])] * m_pmodel->get_probability(m_states[s_p], m_observations[j]) * m_gamma_set[k].data[s_p];
	//				}
	//				alpha_a_z.data[s] *= m_lambda;
	//			}
	//		}
	//		gamma_set[std::tuple<int, int>(i, j)] = alpha_a_z;
	//	}
	//}
	//m_gamma_set.clear();
	//for(size_t i = 0; i < m_belief_points.size(); ++i){

	//}
}

void pomdp::backup_helper(int t){
	int state_count = static_cast<int>(m_states.size());
	int action_count = static_cast<int>(m_actions.size());
	int belief_point_count = static_cast<int>(m_belief_points.size());
	if(t == 0){
		m_policy.assign(belief_point_count, 0); // allocate memory for the policy.
		m_value.assign(belief_point_count, 0.f); // allocate memory for the value.
		for(int i = 0; i < belief_point_count; ++i){
			std::vector<float> reward_array(action_count);
			for(int a = 0; a < action_count; ++a){
				boost::function<float (int)> f = boost::bind(&pomdp::get_reward, this, _1, a);
				reward_array[a] = boost::bind(&pomdp::inner_prod, this, f, m_belief_points[i])();
			}
			auto iter = std::max_element(reward_array.begin(), reward_array.end());
			m_policy[i] = iter - reward_array.begin();
			m_value[i] = *iter;
		}
	}else{
		backup_helper(t-1);
	}
}

float pomdp::inner_prod(const boost::function<float (int)>& f, const point& b){
	float sum = 0.f;
	for(int s = 0; s < static_cast<int>(b.data.size()); ++s){
		sum += f(s);
	}
	return sum;
}