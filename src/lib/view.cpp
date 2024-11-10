#include <sstream>


#include "view.h"

View::Node View::Node::add_child(const Node &child) {
  children.push_back(child);
  return *this;
}

View::Node View::Node::add_child(const std::vector<Node> &children) {
  for (const auto &child: children) {
    this->children.push_back(child);
  }
  return *this;
}

View::Node View::Node::add_props(const Prop &prop) {
  props[prop.first] = prop.second;
  return *this;
}

View::Node View::Node::add_props(const Props &props) {
  for (const auto &[key, value]: props) {
    this->props[key] = value;
  }
  return *this;
}


std::string View::Node::render() {
  std::stringstream stream;
  switch (type) {
    // TODO: Sanitize value
    case NodeType::TEXT:
    case NodeType::CSS:
    case NodeType::JAVASCRIPT:
      stream << value;
      break;

    case NodeType::FRAGMENT:
      for (auto &child: children) {
        stream << child.render();
      }
      break;

    case NodeType::ELEMENT:
      stream << "<" << value;
      for (const auto &[key, value]: props) {
        stream << " " << key << "=\"" << value << "\"";
      }
      stream << ">";
      for (auto &child: children) {
        stream << child.render();
      }
      stream << "</" << value << ">";
      break;
    default:
      break;
  }


  return stream.str();
}


View::Prop View::prop(const std::string &key, const std::string &value) {
  return {key, value};
}
