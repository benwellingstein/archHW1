/* 046267 Computer Architecture - Spring 2017 - HW #1 */
/* This file should hold your implementation of the CPU pipeline core simulator */

#include "sim_api.h"


/*! SIM_CoreReset: Reset the processor core simulator machine to start new simulation
  Use this API to initialize the processor core simulator's data structures.
  The simulator machine must complete this call with these requirements met:
  - PC = 0  (entry point for a program is at address 0)
  - All the register file is cleared (all registers hold 0)
  - The value of IF is the instuction in address 0x0
  \returns 0 on success. <0 in case of initialization failure.
*/





SIM_coreState* coreState = NULL;
bool _stillReading= false;



void _getNextCommand() {
	SIM_cmd newCommand;
	SIM_MemInstRead(coreState->pc, &newCommand);
	coreState->pipeStageState[0].cmd = newCommand;
	coreState->pipeStageState[0].src1Val = 0;
	coreState->pipeStageState[0].src2Val = 0;
}


int SIM_CoreReset(void) {
	coreState = (SIM_coreState*)malloc(sizeof(SIM_coreState));
	if (!coreState) return -1;
	for (int i=0; i< SIM_REGFILE_SIZE; i++) {
		coreState->regFile[i]=0;
	}
	for (int i=0; i< SIM_PIPELINE_DEPTH; i++) {
		coreState->pipeStageState[i].src1Val =0;
		coreState->pipeStageState[i].src2Val =0;
		coreState->pipeStageState[i].cmd.opcode = CMD_NOP;
		coreState->pipeStageState[i].cmd.src1 = 0;
		coreState->pipeStageState[i].cmd.src2 = 0;
		coreState->pipeStageState[i].cmd.isSrc2Imm = false;
		coreState->pipeStageState[i].cmd.dst = 0;
	}
	_getNextCommand();
	return 0;
}

/*! SIM_CoreClkTick: Update the core simulator's state given one clock cycle.
  This function is expected to update the core pipeline given a clock cycle event.
*/
void SIM_CoreClkTick() {
	
}

/*! SIM_CoreGetState: Return the current core (pipeline) internal state
    curState: The returned current pipeline state
    The function will return the state of the pipe at the end of a cycle
*/
void SIM_CoreGetState(SIM_coreState *curState) {
	*curState = *coreState;
}



