#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <unordered_map>
#include <vector>

#define NODE_ELEMENT(name)                                                  \
  inline Node name() {                                                      \
    return Node(NodeType::ELEMENT, #name);                                  \
  }                                                                         \
  inline Node name(const Node& children) {                                  \
    return Node(NodeType::ELEMENT, #name).add_child(children);              \
  }                                                                         \
  inline Node name(const std::vector<Node>& children) {                     \
    return Node(NodeType::ELEMENT, #name).add_child(children);              \
  }                                                                         \
  inline Node name(const std::string& value) {                              \
    return Node(NodeType::ELEMENT, #name).add_child(text(value));           \
  }                                                                         \
  inline Node name(const Props& props, const std::vector<Node>& children) { \
    return Node(NodeType::ELEMENT, #name)                                   \
        .add_props(props)                                                   \
        .add_child(children);                                               \
  }

#define NODE_ELEMENT_TEXT(name, nodeType)      \
  inline Node name(const std::string& value) { \
    return Node(nodeType, value);              \
  }

namespace View {
  enum class NodeType {
    TEXT,
    CSS,
    JAVASCRIPT,
    ELEMENT,
    FRAGMENT,
  };

  typedef std::unordered_map<std::string, std::string> Props;
  typedef std::pair<std::string, std::string> Prop;

  class Node {
    NodeType type;
    std::string value;
    std::vector<Node> children;
    Props props;

  public:
    explicit Node(const NodeType type, std::string value) :
        type(type), value(std::move(value)) {}

    explicit Node(const NodeType node) : type(node){};

    Node add_child(const Node& child);

    Node add_child(const std::vector<Node>& children);

    Node add_props(const Prop& prop);

    Node add_props(const Props& props);

    std::string render();
  };

  NODE_ELEMENT_TEXT(text, NodeType::TEXT);
  NODE_ELEMENT_TEXT(css, NodeType::CSS);
  NODE_ELEMENT_TEXT(js, NodeType::JAVASCRIPT);

  NODE_ELEMENT(title);
  NODE_ELEMENT(style);
  NODE_ELEMENT(head);
  NODE_ELEMENT(body);
  NODE_ELEMENT(h1);
  NODE_ELEMENT(h2);
  NODE_ELEMENT(h3);
  NODE_ELEMENT(h4);
  NODE_ELEMENT(h5);
  NODE_ELEMENT(h6);
  NODE_ELEMENT(p);
  NODE_ELEMENT(div);
  NODE_ELEMENT(span);
  NODE_ELEMENT(header);
  NODE_ELEMENT(footer);

  inline Node fragment() {
    return Node(NodeType::FRAGMENT);
  }

  inline Node fragment(const Node& children) {
    return Node(NodeType::FRAGMENT).add_child(children);
  }

  inline Node fragment(const std::vector<Node>& children) {
    return Node(NodeType::FRAGMENT).add_child(children);
  }

  inline Node html(const std::vector<Node>& children) {
    return fragment({text("<!doctype html>"),
                     Node(NodeType::ELEMENT, "html").add_child(children)});
  }

  inline Node html(const Props& props, const std::vector<Node>& children) {
    return fragment(
        {text("<!doctype html>"),
         Node(NodeType::ELEMENT, "html").add_child(children).add_props(props)});
  }
} // namespace View

#endif // VIEW_H
