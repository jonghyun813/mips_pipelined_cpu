#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "DigitalCircuit.h"

class Control : public DigitalCircuit {

  public:

    Control(const Wire<6> *iOpcode,
            Wire<1> *oRegDst,
            Wire<1> *oALUSrc,
            Wire<1> *oMemToReg,
            Wire<1> *oRegWrite,
            Wire<1> *oMemRead,
            Wire<1> *oMemWrite,
            Wire<1> *oBranch,
            Wire<2> *oALUOp) : DigitalCircuit("Control") {
      _iOpcode = iOpcode;
      _oRegDst = oRegDst;
      _oALUSrc = oALUSrc;
      _oMemToReg = oMemToReg;
      _oRegWrite = oRegWrite;
      _oMemRead = oMemRead;
      _oMemWrite = oMemWrite;
      _oBranch = oBranch;
      _oALUOp = oALUOp;
    }

    virtual void advanceCycle() {
      /* FIXME */
      _oRegDst->reset();
      _oALUSrc->reset();
      _oMemToReg->reset();
      _oRegWrite->reset();
      _oMemRead->reset();
      _oMemWrite->reset();
      _oBranch->reset();
      _oALUOp->reset();
      _oALUOp->reset();

      switch(_iOpcode->to_ulong()) {
        case 0x00:
          _oRegDst->set(0);
          _oALUSrc->reset(0);
          _oMemToReg->reset(0);
          _oRegWrite->set(0);
          _oMemRead->reset(0);
          _oMemWrite->reset(0);
          _oBranch->reset(0);
          _oALUOp->set(1);
          _oALUOp->reset(0);
          break;

        case 0x23:
          _oRegDst->reset(0);
          _oALUSrc->set(0);
          _oMemToReg->set(0);
          _oRegWrite->set(0);
          _oMemRead->set(0);
          _oMemWrite->reset(0);
          _oBranch->reset(0);
          _oALUOp->reset(1);
          _oALUOp->reset(0);
          break;
        
        case 0x2b:
          _oRegDst->reset(0);
          _oALUSrc->set(0);
          _oMemToReg->reset(0);
          _oRegWrite->reset(0);
          _oMemRead->reset(0);
          _oMemWrite->set(0);
          _oBranch->reset(0);
          _oALUOp->reset(1);
          _oALUOp->reset(0);
          break;

        case 0x04:
          _oRegDst->reset(0);
          _oALUSrc->reset(0);
          _oMemToReg->reset(0);
          _oRegWrite->reset(0);
          _oMemRead->reset(0);
          _oMemWrite->reset(0);
          _oBranch->set(0);
          _oALUOp->reset(1);
          _oALUOp->set(0);
          break;

        case 0x08:
          _oRegDst->reset(0);
          _oALUSrc->set(0);
          _oMemToReg->reset(0);
          _oRegWrite->set(0);
          _oMemRead->reset(0);
          _oMemWrite->reset(0);
          _oBranch->reset(0);
          _oALUOp->reset(1); 
          _oALUOp->reset(0);
          break;
        // add(00), sub(00), addi(08), and(00), or(00), nor(00), slt(00), lw(23), sw(2b), beq(04)
      }
    }

  private:

    const Wire<6> *_iOpcode;
    Wire<1> *_oRegDst;
    Wire<1> *_oALUSrc;
    Wire<1> *_oMemToReg;
    Wire<1> *_oRegWrite;
    Wire<1> *_oMemRead;
    Wire<1> *_oMemWrite;
    Wire<1> *_oBranch;
    Wire<2> *_oALUOp;

};

#endif

