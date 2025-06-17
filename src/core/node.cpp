#include "node.h"
#include <raylib.h>

Node::Node() {}

Node::~Node() {}

void Node::Update() {}

void Node::Draw() const { DrawRectangleRec(current_transform_.Rec(), RED); }

void Node::Register() { TraceLog(LOG_DEBUG, "Node Register"); }

void Node::Remove() { TraceLog(LOG_DEBUG, "Node Remove"); }

void Node::Hover() { TraceLog(LOG_DEBUG, "Node Hover"); }

void Node::Click() { TraceLog(LOG_DEBUG, "Node Click"); }

void Node::Drag() { TraceLog(LOG_DEBUG, "Node Drag"); }
