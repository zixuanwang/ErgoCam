#pragma once
#include "action.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <opencv2/opencv.hpp>
#include "point.h"
#include <random>
#include "simple_model.h"
#include "state.h"
#include <vector>

// states are discrete
class pomdp
{
public:
	pomdp(void);
	~pomdp(void);
	void init(); // initialize states, actions and observations.
	void expand(int g); // uniformly sample g points from the belief space.
	void backup();
	void backup_helper(int t); // recursion helper.
	float get_reward(int s, int a){return m_reward_map[std::tuple<int, int>(s, a)];}
	float inner_prod(const boost::function<float (int)>& f, const point& b);
private:
	std::vector<state> m_states; // the set of states defined in this problem.
	std::vector<action> m_actions; // the set of actions defined in this problem.
	std::vector<feature_vector> m_observations; // the set of observations defined in this problem.
	boost::unordered_map<std::tuple<int, int, int>, float> m_transition_map; // define the transitional probability: <state, action, state>.
	boost::unordered_map<std::tuple<int, int>, float> m_reward_map; // define the reward function: <state, action>.
	boost::shared_ptr<generative_model> m_pmodel;
	std::vector<point> m_belief_points;
	std::vector<int> m_policy; // the optimal policy for each belief point.
	std::vector<float> m_value; // the optimal value for each belief point.
	std::vector<point> m_gamma_set; // store the optimal hyper plane for each belief point.
	int m_T; // the horizon size.
	float m_lambda; // the discount factor.

};

