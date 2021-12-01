#include <Arduino.h>
#include "qpn.h"
#include "QHSM_Test.h"
Q_DEFINE_THIS_FILE;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("QHSM Testing...");
  QHsmTst_ctor();
  QHSM_INIT(super_QHsmTst);
  Serial.print('\n');
}

void loop() {
  // put your main code here, to run repeatedly:
  char ue;
  if(Serial.available() > 0){
    ue = Serial.read();
    if(ue == 'a' || ue == 'A'){
      Q_SIG(super_QHsmTst) = (QSignal)A_SIG;
    }
    else if (ue == 'b'  || ue == 'B') Q_SIG(super_QHsmTst) = (QSignal)B_SIG;
    else if (ue == 'c'  || ue == 'C') Q_SIG(super_QHsmTst) = (QSignal)C_SIG;
    else if (ue == 'd'  || ue == 'D') Q_SIG(super_QHsmTst) = (QSignal)D_SIG;
    else if (ue == 'e'  || ue == 'E') Q_SIG(super_QHsmTst) = (QSignal)E_SIG;
    else if (ue == 'f'  || ue == 'F') Q_SIG(super_QHsmTst) = (QSignal)F_SIG;
    else if (ue == 'g'  || ue == 'G') Q_SIG(super_QHsmTst) = (QSignal)G_SIG;
    else if (ue == 'h'  || ue == 'H') Q_SIG(super_QHsmTst) = (QSignal)H_SIG;
    else if (ue == 'i'  || ue == 'I') Q_SIG(super_QHsmTst) = (QSignal)I_SIG;
    else if (ue == 'x'  || ue == 'X') Q_SIG(super_QHsmTst) = (QSignal)TERMINATE_SIG;
    else Q_SIG(super_QHsmTst) = IGNORE_SIG;

    QHSM_DISPATCH(super_QHsmTst);
    Serial.print('\n');
  }

}


Q_NORETURN Q_onAssert	(	char_t const Q_ROM *const 	module,int_t const 	location ){

  Serial.println("Assertion failure!!");
  Serial.println((String)module);
  Serial.println(location);
  while(1);
}	