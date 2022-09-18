#include <iostream>
#include <memory>

#include "graphedge.h"
#include "graphnode.h"

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{
    //// STUDENT CODE -> DONE
    ////

    // Not every GraphNode needs to delete _chatBot
    // delete _chatBot;

    ////
    //// EOF STUDENT CODE
}

GraphNode::GraphNode(const GraphNode &source) // copy constructor
{
    std::cout << "GraphNode Copy Constructor" << std::endl;

    for (auto it = std::begin(source._childEdges); it != std::end(source._childEdges); ++it)
    {
        GraphEdge edge = *((*it).get());
        _childEdges.push_back(std::make_unique<GraphEdge>(edge.GetID()));
    }

    for (auto it = std::begin(source._parentEdges); it != std::end(source._parentEdges); ++it)
    {
        GraphEdge edge = *(*it);
        _parentEdges.push_back(new GraphEdge(edge.GetID()));
    }

    for (auto it = std::begin(source._answers); it != std::end(source._answers); ++it)
    {
        std::string answer = *it;
        _answers.push_back(answer);
    }

    _chatBot = source._chatBot;
    _id = source._id;
}

GraphNode::GraphNode(GraphNode &&source) // move constructor
{
    std::cout << "GraphNode Move Constructor" << std::endl;

    for (auto it = std::begin(source._childEdges); it != std::end(source._childEdges); ++it)
    {
        std::unique_ptr<GraphEdge> edge = std::move(*it);
        _childEdges.push_back(std::move(edge));
    }

    for (auto it = std::begin(source._parentEdges); it != std::end(source._parentEdges); ++it)
    {
        GraphEdge edge = *(*it);
        _parentEdges.push_back(&edge);
    }

    for (auto it = std::begin(source._answers); it != std::end(source._answers); ++it)
    {
        std::string answer = *it;
        _answers.push_back(answer);
    }


    source._childEdges.clear();
    source._parentEdges.clear();
    source._answers.clear();

    _chatBot = std::move(source._chatBot);

}

GraphNode &GraphNode::operator=(const GraphNode &source) // copy assignment operator
{
    std::cout << "GraphNode Copy Assignment Operator" << std::endl;

    if (this == &source)
        return *this;

    _childEdges.clear();
    for (auto it = std::begin(source._childEdges); it != std::end(source._childEdges); ++it)
    {
        GraphEdge edge = *((*it).get());
        _childEdges.push_back(std::make_unique<GraphEdge>(edge.GetID()));
    }

    _parentEdges.clear();
    for (auto it = std::begin(source._parentEdges); it != std::end(source._parentEdges); ++it)
    {
        GraphEdge edge = *(*it);
        _parentEdges.push_back(new GraphEdge(edge.GetID()));
    }

    _answers.clear();
    for (auto it = std::begin(source._answers); it != std::end(source._answers); ++it)
    {
        std::string answer = *it;
        _answers.push_back(answer);
    }

    _chatBot = source._chatBot;
    _id = source._id;

    return *this;
}

GraphNode &GraphNode::operator=(GraphNode &&source) // move assignment operator
{
    std::cout << "GraphNode Move Assignment Operator" << std::endl;

    if (this == &source)
        return *this;

    _childEdges.clear();
    for (auto it = std::begin(source._childEdges); it != std::end(source._childEdges); ++it)
    {
        std::unique_ptr<GraphEdge> edge = std::move(*it);
        _childEdges.push_back(std::move(edge));
    }

    _parentEdges.clear();
    for (auto it = std::begin(source._parentEdges); it != std::end(source._parentEdges); ++it)
    {
        GraphEdge edge = *(*it);
        _parentEdges.push_back(&edge);
    }

    _answers.clear();
    for (auto it = std::begin(source._answers); it != std::end(source._answers); ++it)
    {
        std::string answer = *it;
        _answers.push_back(answer);
    }

    source._childEdges.clear();
    source._parentEdges.clear();
    source._answers.clear();

    _chatBot = std::move(source._chatBot);
    

    return *this;
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge)
{
    _childEdges.push_back(std::move(edge));
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(ChatBot chatbot)
{
    _chatBot = std::move(chatbot);
    _chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(_chatBot);
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////

    return _childEdges[index].get();

    ////
    //// EOF STUDENT CODE
}