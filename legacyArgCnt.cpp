#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Type.h"

using namespace llvm;

namespace{
    struct legacyArgCnt: public FunctionPass{
        static char ID;
        legacyArgCnt():FunctionPass(ID){}

        bool runOnFunction(Function &F) override{
            int argCnt = 0;
            int fpArgCnt = 0;
            for(auto &arg : F.args()){
                argCnt++;
                if(arg.getType()->isFloatingPointTy()){
                    fpArgCnt++;
                }
            }
            errs().write_escaped(F.getName())<<"\t"<<argCnt<<"\t"<<fpArgCnt<<"\n";
            return false;
        }

    };
}

char legacyArgCnt::ID = 0;
static RegisterPass<legacyArgCnt> X("legacy-arg-cnt","Argument counter realized by legacy.");