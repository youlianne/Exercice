#include "network.h"
#include "random.h"
#include <algorithm>


void Network::resize(const size_t& val){
	values.resize(val);
	RNG.normal(values);
}

bool Network::add_link(const size_t& a, const size_t& b){
	if (a==b or a<0 or b<0 or a>=values.size() or b>=values.size()){
		return false;
	}
	
	for (auto I: links){
		if((I.first == a and I.second == b) or (I.first == b and I.second == a)){
			return false;
		}
	}
	links.insert(std::make_pair(a,b));
	links.insert(std::make_pair(b,a));
	
	return true;
}

size_t Network::random_connect(const double& mean_deg){
	
	links.clear();
	
	size_t count (0);
	std::vector<int> poiss(values.size());
	RNG.poisson(poiss,mean_deg);
	
	std::vector<int> n (values.size());
	RNG.uniform_int(n,0,values.size()-1);
	
	std::vector<size_t> it (values.size());
	std::iota(it.begin(),it.end(),0);
	
	
	
	for (int i(0); i<values.size(); ++i){
		RNG.shuffle(it);
		for (size_t j(0);j<poiss[i];++j){
			if (add_link(i,n[it[j]])) ++count;
		}
	}
	
	return count;
}

size_t Network::set_values(const std::vector<double>& v){
	
	size_t val = v.size();
	
	if (v.size() > values.size()){
		val = values.size();
	}
	for (size_t i(0);i<val;++i){
		values[i]= v[i];
	}
	
	return val;
}

size_t Network::size() const{
	return values.size();
}

size_t Network::degree(const size_t &_n) const{
	size_t count(0);
	for (auto I : links){
		if (I.first == _n){
			++count;
		}
	}
	return count;
}

double Network::value(const size_t &_n) const{
	return values[_n];
}

std::vector<double> Network::sorted_values() const{
	std::vector<double> sorted = values;
	std::sort(sorted.begin(), sorted.end(), std::greater<double>());
	
	return sorted;
}

std::vector<size_t> Network::neighbors(const size_t& a) const{
	std::vector<size_t> neighbors;
	for (auto I : links){
		if(I.first == a){
			neighbors.push_back(I.second);
		}
	}
	return neighbors;
}
