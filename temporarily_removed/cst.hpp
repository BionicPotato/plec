#pragma once

#include <list>
#include "cstnode.hpp"
#include "lexer.hpp"

class CST
{
    public:
        std::list<CSTNode*> topNodes;
        std::list<CSTNode> nodes;

        bool addNode(Token tok);
        void parse();
    
    private:
        void parseBlocks(std::list<CSTNode*>& nodeList);
        //void parseFlowControl(std::list<CSTNode*>& nodeList);
        //void parseSemicolons(std::list<CSTNode*>& nodeList);
        void parseStatements(std::list<CSTNode*>& nodeList);
        void parseTypes(std::list<CSTNode*>& nodeList);
        void parseOperators(std::list<CSTNode*>& nodeList);
        static bool comparePrecedence(const std::list<CSTNode*>::iterator it1, const std::list<CSTNode*>::iterator it2);
};
