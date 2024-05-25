#include "llvm/ADT/Statistic.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Type.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/PassManager.h"

using namespace llvm;

namespace{
    struct newArgCnt: public PassInfoMixin<newArgCnt>{
        PreservedAnalyses run(Function &F,FunctionAnalysisManager &FAM){
            int argCnt = 0;
            int fpArgCnt = 0;
            for(auto &arg : F.args()){
                argCnt++;
                if(arg.getType()->isFloatingPointTy()){
                    fpArgCnt++;
                }
            }
            errs().write_escaped(F.getName())<<"\t"<<argCnt<<"\t"<<fpArgCnt<<"\n";
            return PreservedAnalyses::all();
        }
    };
}

extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK
llvmGetPassPluginInfo(){
    return{
        LLVM_PLUGIN_API_VERSION,"new-arg-cnt","v0.1",
        [](PassBuilder &PB){
            PB.registerPipelineParsingCallback(
                [](StringRef PassName,FunctionPassManager &FPM,
                ArrayRef<PassBuilder::PipelineElement>){
                    if(PassName=="new-arg-cnt"){
                        FPM.addPass(newArgCnt());
                        return true;
                    }
                    return false;
                }
            );
        }
    };
}