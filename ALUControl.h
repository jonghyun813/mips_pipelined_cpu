#ifndef __ALU_CONTROL_H__
#define __ALU_CONTROL_H__

#include "DigitalCircuit.h"

#include <cassert>

class ALUControl : public DigitalCircuit {

  public:

    ALUControl(const Wire<2> *iALUOp,
               const Wire<6> *iFunct,
               Wire<4> *oOperation) : DigitalCircuit("ALUControl") {
      _iALUOp = iALUOp;
      _iFunct = iFunct;
      _oOperation = oOperation;
    }

    virtual void advanceCycle() {
      /* FIXME */

      _oOperation->reset();
      Wire<6> mask = 0b001111;

      if(!(_iALUOp->test(0)) && !(_iALUOp->test(1))) {
        *_oOperation = 0b0010;
      }
      else if(_iALUOp->test(0)) {
        *_oOperation = 0b0110;
      }
      else if(_iALUOp->test(1)) {
        Wire<6> lowest_4bits = (*_iFunct & mask);
        switch(lowest_4bits.to_ulong()) {
          case 0b0000:
            *_oOperation = 0b0010;
            break;
          case 0b0010:
            *_oOperation = 0b0110;
            break;
          case 0b0100:
            *_oOperation = 0b0000;
            break;
          case 0b0101:
            *_oOperation = 0b0001;
            break;
          case 0b1010:
            *_oOperation = 0b0111;
            break;
          case 0b0111:
            *_oOperation = 0b1100;
            break;
        }
      }
    }

  private:

    const Wire<2> *_iALUOp;
    const Wire<6> *_iFunct;
    Wire<4> *_oOperation;

};

#endif

