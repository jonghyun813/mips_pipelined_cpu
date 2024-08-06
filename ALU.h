#ifndef __ALU_H__
#define __ALU_H__

#include "DigitalCircuit.h"

#include <cassert>

class ALU : public DigitalCircuit {

  public:

    ALU(const Wire<4> *iALUControl,
        const Wire<32> *iInput0,
        const Wire<32> *iInput1,
        Wire<32> *oOutput,
        Wire<1> *oZero) : DigitalCircuit("ALU") {
      _iALUControl = iALUControl;
      _iInput0 = iInput0;
      _iInput1 = iInput1;
      _oOutput = oOutput;
      _oZero = oZero;
    }

    virtual void advanceCycle() {
      /* FIXME */

      unsigned tmp = 0;
      Wire<32> one;
      _oOutput->reset();

      switch((*_iALUControl).to_ulong()) {
        case 0b0000:
          for(size_t i = 0; i < 32; i++) {
            _oOutput->set(i, (_iInput0->test(i) && _iInput1->test(i)) ? true : false);
          }
          break;

        case 0b0001:
          for(size_t i = 0; i < 32; i++) {
            _oOutput->set(i, (_iInput0->test(i) || _iInput1->test(i)) ? true : false);
          }          
          break;

        case 0b0010:
          for(size_t i = 0; i < 32; i++) {
            if (_iInput0->test(i)) { tmp++; }
            if (_iInput1->test(i)) { tmp++; }

            _oOutput->set(i, (tmp % 2) == 1 ? true : false);

            tmp /= 2;
          }
          break;

        case 0b0110:
          one = (unsigned long long)0x01;

          *_oOutput = ~(*_iInput1);

          for(size_t i = 0; i < 32; i++) {
            if (_oOutput->test(i)) { tmp++; }
            if (one.test(i)) { tmp++; }

            _oOutput->set(i, (tmp % 2) == 1 ? true : false);

            tmp /= 2;
          }

          tmp = 0;
          for(size_t i = 0; i < 32; i++) {
            if (_iInput0->test(i)) { tmp++; }
            if (_oOutput->test(i)) { tmp++; }

            _oOutput->set(i, (tmp % 2) == 1 ? true : false);

            tmp /= 2;
          }
          break;

        case 0b0111:
          if (_iInput0->to_ulong() < _iInput1->to_ulong()) {
            _oOutput->set(0);
          }
          break;

        case 0b1100:
          for(size_t i = 0; i < 32; i++) {
            _oOutput->set(i, (!(_iInput0->test(i)) && !(_iInput1->test(i))) ? true : false);
          }
          break;
      }

      if(_oOutput->none()) {
        _oZero->set(0);
      }
      else {
        _oZero->reset(0);
      }
    }

  private:

    const Wire<4> *_iALUControl;
    const Wire<32> *_iInput0;
    const Wire<32> *_iInput1;
    Wire<32> *_oOutput;
    Wire<1> *_oZero;

};

#endif

