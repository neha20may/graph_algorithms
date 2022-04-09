//
// Created by neha2 on 16-03-2022.
//

#include <bits/stdc++.h>
#include "flow_edge.h"

using namespace std;

int flow_edge::from() { return from_; };

int flow_edge::to() { return to_; };

int flow_edge::other(int vertex) {
    if (vertex == to_) return from_;
    else if (vertex == from_) return to_;
    else throw invalid_argument("illgeal endpoint");
}

double flow_edge::capacity() { return capacity_; };

double flow_edge::flow() { return flow_; };

double flow_edge::residual_capacity(int v) const {
    if (v == from_) return flow_;
    else if (v == to_) return capacity_ - flow_;
    else throw invalid_argument("illegal end point to calculate the residual and capacity");
}; //residual capacity towrds v
void flow_edge::add_residual_flow_to(int v, double delta) {
    if (v == from_) flow_ -= delta; //increase flow hence residual decreases
    if (v == to_) flow_ += delta; //increase the flow so oppposite side me it increases
}; //add delta flow towards v


std::ostream &operator<<(ostream &os, const flow_edge &e) {
    os << "edge from:" << e.from_ << "----->" << e.to_ << endl;
    os << "flow from:" << e.from_ << "-----" << e.flow_ << "--->to: " << e.to_ << endl;
    os << "residual " << e.from_ << "-----" << e.residual_capacity(e.to_) << " ---> " << e.to_ << endl;
    os << "negation " << e.from_ << "<-----" << e.residual_capacity(e.from_) << "--- " << e.to_ << endl;
    return os;
};
