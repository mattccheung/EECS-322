#pragma once

#include <vector>
#include <string>
#include <map>

#include "tree.h"

using namespace std;


namespace L3 {

    enum OP {
        NOP, ADDQ, SUBQ, IMULQ, ANDQ, SALQ, SARQ
    };

    inline OP parseOp(string &s) {
        return s == "+" ? ADDQ :
               (s == "-" ? SUBQ :
                (s == "*" ? IMULQ :
                 (s == "&" ? ANDQ :
                  (s == "<<" ? SALQ :
                   (s == ">>" ? SARQ : NOP)))));
    }

    inline string opToString(OP op) {
        return op == ADDQ ? "+" :
               (op == SUBQ ? "-" :
                (op == IMULQ ? "*" :
                 (op == ANDQ ? "&" :
                  (op == SALQ ? "<<" :
                   (op == SARQ ? ">>" : "NOP")))));
    }

    enum CMP {
        NCMP, LT, LE, EQ, GE, GT
    };

    inline CMP parseCmp(string &s) {
        return s == "<" ? LT :
               (s == "<=" ? LE :
                (s == "=" ? EQ :
                 (s == ">=" ? GE :
                  (s == ">" ? GT : NCMP))));
    }

    inline string cmpToString(CMP cmp) {
        return cmp == LT ? "<" :
               (cmp == LE ? "<=" :
                (cmp == EQ ? "=" :
                 (cmp == GE ? ">=" :
                  (cmp == GT ? ">" : "NCMP"))));
    }

    struct Instruction {
        virtual ~Instruction() {};

        virtual void print(ostream &os) = 0;

        virtual vector <string> toL2(const map<string, string> &labelMap) = 0;

        virtual TreeNode *getInstTree() = 0;
    };

    ostream &operator<<(ostream &os, Instruction &inst);

    struct AssignInst : public Instruction {
        string var, s;

        ~AssignInst();

        void print(ostream &os);

        vector <string> toL2(const map<string, string> &labelMap);

        TreeNode *getInstTree();
    };

    struct AssignOpInst : public Instruction {
        string var, lt, rt;
        OP op;

        ~AssignOpInst();

        void print(ostream &os);

        vector <string> toL2(const map<string, string> &labelMap);

        TreeNode *getInstTree();
    };

    struct AssignCmpInst : public Instruction {
        string var, lt, rt;
        CMP cmp;

        ~AssignCmpInst();

        void print(ostream &os);

        vector <string> toL2(const map<string, string> &labelMap);

        TreeNode *getInstTree();
    };

    struct LoadInst : public Instruction {
        string lvar, rvar;

        ~LoadInst();

        void print(ostream &os);

        vector <string> toL2(const map<string, string> &labelMap);

        TreeNode *getInstTree();
    };

    struct StoreInst : public Instruction {
        string var, s;

        ~StoreInst();

        void print(ostream &os);

        vector <string> toL2(const map<string, string> &labelMap);

        TreeNode *getInstTree();
    };

    struct BranchInst : public Instruction {
        string var, llabel, rlabel;

        ~BranchInst();

        void print(ostream &os);

        vector <string> toL2(const map<string, string> &labelMap);

        TreeNode *getInstTree();
    };

    struct LabelInst : public Instruction {
        string label;

        ~LabelInst();

        void print(ostream &os);

        vector <string> toL2(const map<string, string> &labelMap);

        TreeNode *getInstTree();
    };

    struct ReturnInst : public Instruction {
        string var;

        ~ReturnInst();

        void print(ostream &os);

        vector <string> toL2(const map<string, string> &labelMap);

        TreeNode *getInstTree();
    };

    struct AssignCallInst : public Instruction {
        string var, callee;
        vector <string> args;

        ~AssignCallInst();

        void print(ostream &os);

        vector <string> toL2(const map<string, string> &labelMap);

        TreeNode *getInstTree();
    };

    struct Function {
        string name;
        vector <string> arguments;
        vector<Instruction *> instructions;

        ~Function();

        vector<TreeNode *> getInstTrees();
    };

    struct Program {
        string name;
        vector<Function *> functions;

        ~Program();

        vector <string> toL2();
    };

}
