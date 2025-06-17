#pragma once

#include <raylib.h>

struct NodeTransform {
  float x, y;
  float w, h;  // width & height
  float r, s;  // rotation(radian) & scale

  Rectangle Rec() const { return {x, y, w, h}; }
};

class Node {
public:
  Node();
  virtual ~Node();

  virtual void Update() = 0;
  virtual void Draw() const = 0;

  // TODO: parent tree structure <2025-06-17 12:31, @qiekn> //
  // TODO: 用来做一个 层级结构，这样不用单独计算每一个子节点的 transform
  // <2025-06-17 12:31, @qiekn> // void SetContainer(Node parent); void Get

  void Register();
  void Remove();

  virtual void Hover();
  virtual void Click();
  virtual void Drag();

private:
  /* data */
  NodeTransform target_transform_;
  NodeTransform current_transform_;
};
