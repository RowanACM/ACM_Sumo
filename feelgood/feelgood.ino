#include <PololuBuzzer.h>
PololuBuzzer buzzer;
const char FEELGOOD[] PROGMEM = "L4 V16 T130"
  "O2 E- L8 R E-FG- R B R L4 B-"
  "O4 L8 F R L4 E-"
  "O2 R16 L4 A- L8 RA- BB-RG-R L4 E-"
  "O4 L8 F R L4 E-"
  "O2 E- L8 R E-FG- R B R L4 B-"
  "O4 L8 F R L4 E-"
  "O2 R16 L4 A- L8 RA- BB-RG-R L4 E-"
  "O4 L8 F R L4 E-"
  "O4 L8 F L4 E- L8 BBB-B- L4 A L8 AA A- L4 A-G- R8 E- L8 E-E-G-G- L4 E- L8 G-G-E- L4 G-E- R4 L8 B-BBB-B- L4 A L8 AAA- L4 A-G-R8 L8 G- L4 A- L8 A-A-A-A-A-A-A-A- L4 G- E- R L8 B-BBB-B-AAAAA-A-A- L4 G- R L8 E-E-G-G- L4 E- L8 G-G- E- L4 G- E- R L8 BBB-B- A4 AA A- L4 A- G- L8 R G- L4 A- L8 A-A-A-A-A-A-A-B- L4 A-G-E-"
  "O3 L8 E- L4 D- O2 B- L8 A- G- L2 E- L4 E- L2 E-"
  "O5 L8 E- L4 FG-A-B- O6 D- O5 L2 B- L4 A- L8 G- L4 E-G-A-F L2 D- L8 E- L4 FG-A-B- O6 D- O5 L2 B- L4 A- L8 G- L4 E-G- L2 A- L4 F L8 D- L4 E- L8 F L4 G- A- B- O6 D- O5 L2 B- A- L8 G- L4 E- G- A- F L2 D- L8 E- L4 F G- A- B- O6 D- O5 B- A- L2 A- L8 G- L4 E- G- L32 G- L1 A- R2"
  "O5 L16 B-RB-RB-RA-R L4 B- L8 A-R L4 B- L8 A-R L4 B- L8 A-R L16 B-B-B-RB-R O6 D-R O5 L4 B- L8 A-RA- L16 B-R L8 A- L16 B-R L8 A- L16 A-B- R4 A-RB-RA-RB-RA-B-R L4 A- L8 G- E-E-E-E- L16 D-D- L8 D- E-RE-E- L16 E-E- L8 E- L16 D-D- L8 D-E-E-B-A-G-A-B-A-G-G-B-A-G- L2 B- L16 R8 B-B-B- O6 L4 D- O5 B- L8 B- L4 O6 D- O5 B- L8 B- O6 L4 D- O5 B- L8 B- A- L16 A- L8 B-RB-B- L16 B- L8 B-RB-B- L16 B- L8 B-RB- L4 O6 D- O5 B- L8 B- A- L16 A- L8 B-RB-B-RB-RA-B-A-B-RB-B-A-B-A-A-A-B-A-G-A-B-A-G-G- L32 A-B-RA-B-RA-B-RA- L2 B- "
  "O2 L4 E- L8 R E-FG- R B R L4 B-"
  "O4 L8 F R L4 E-"
  "O2 R16 L4 A- L8 RA- BB-RG-R L4 E-"
  "O4 L8 F R L4 E-"
  "O2 E- L8 R E-FG- R B R L4 B-"
  "O4 L8 F R L4 E-"
  "O2 R16 L4 A- L8 RA- BB-RG-R L4 E-"
  "O4 L8 F R L4 E-"
  "O3 L4 E- L2 G- L8 E- L4 G- D- L2 F L8 D- L4 F <B L2 E- L8 <B L4 E- D- L2 F L8 D- L4 F"
  "O5 L8 B- L4 A-B-A-B-A-B-A-B-A-B-A-B-A- L2 B- O4 L8 E- L4 FG-A-B- O5 D- O4 L2 B- L4 A- L8 G- L4 E-G- L2 A- L8 FE- L2 D- L8 R E- L4 FG-A-B- O5 D- O4 L2 B- R4 L8 A- L4 G-E-G- L1 A- L8 F E-D-"
  "O4 L8 E- L4 FG-A-B- O5 D- O4 L2 B- L4 A- L8 G- L4 E-G- L2 A- L8 FE- L2 D- L8 R E- L4 FG-A-B- O5 D- O4 L2 B- R4 L8 A- L4 G-E-G- L1 A-"
  "O5 L8 RB-B-RB-RA-B-A-B-RB-B-A-B-A-A-A-B-A-G-A-B-A-G-G- L32 A-B-RA-B-RA-B-RA- L8 RB-B-RB-RA-B-A-B-RB-B-A-B-A-A-A-B-A-G-A-B-A-G-G- L32 A-B-RA-B-RA-B-RA- L2 B-"
  "O2 L4 E- L8 R E-FG- R B R L4 B-"
  "O4 L8 F R L4 E-"
  "O2 R16 L4 A- L8 RA- BB-RG-R L4 E-"
  "O4 L8 F R L4 E-"
  "O2 E- L8 R E-FG- R B R L4 B-"
  "O4 L8 F R L4 E-"
  "O2 R16 L4 A- L8 RA- BB-RG-R L4 E-"
  "O4 L8 F R L4 E-";
void setup() {
  // put your setup code here, to run once:
  buzzer.playFromProgramSpace(FEELGOOD);
  //buzzer.play("L4 V16 T130"
  //"O2 E- L8 R E-FG- R B R L4 B-"
  //"O4 L8 F R L4 E-"
  //"O2 R16 L4 A- L8 RA- BB-RG-R L4 E-"
  //"O4 L8 F R L4 E-"
  //"O2 E- L8 R E-FG- R B R L4 B-"
  //"O4 L8 F R L4 E-"
  //"O2 R16 L4 A- L8 RA- BB-RG-R L4 E-"
  //"O4 L8 F R L4 E-"
  //"O4 L8 F L4 E- L8 BBB-B- L4 A L8 AA A- L4 A-G- R8 E- L8 E-E-G-G- L4 E- L8 G-G-E- L4 G-E- R4 L8 B-BBB-B- L4 A L8 AAA- L4 A-G-R8 L8 G- L4 A- L8 A-A-A-A-A-A-A-A- L4 G- E- R L8 B-BBB-B-AAAAA-A-A- L4 G- R L8 E-E-G-G- L4 E- L8 G-G- E- L4 G- E- R L8 BBB-B- A4 AA A- L4 A- G- L8 R G- L4 A- L8 A-A-A-A-A-A-A-B- L4 A-G-E-"
  //"O3 L8 E- L4 D- O2 B- L8 A- G- L2 E- L4 E- L2 E-"
  //"O5 L8 E- L4 FG-A-B- O6 D- O5 L2 B- L4 A- L8 G- L4 E-G-A-F L2 D- L8 E- L4 FG-A-B- O6 D- O5 L2 B- L4 A- L8 G- L4 E-G- L2 A- L4 F L8 D- L4 E- L8 F L4 G- A- B- O6 D- O5 L2 B- A- L8 G- L4 E- G- A- F L2 D- L8 E- L4 F G- A- B- O6 D- O5 B- A- L2 A- L8 G- L4 E- G- L32 G- L1 A- R2"
  //"O5 L16 B-RB-RB-RA-R L4 B- L8 A-R L4 B- L8 A-R L4 B- L8 A-R L16 B-B-B-RB-R O6 D-R O5 L4 B- L8 A-RA- L16 B-R L8 A- L16 B-R L8 A- L16 A-B- R4 A-RB-RA-RB-RA-B-R L4 A- L8 G- E-E-E-E- L16 D-D- L8 D- E-RE-E- L16 E-E- L8 E- L16 D-D- L8 D-E-E-B-A-G-A-B-A-G-G-B-A-G- L2 B- L16 R8 B-B-B- O6 L4 D- O5 B- L8 B- L4 O6 D- O5 B- L8 B- O6 L4 D- O5 B- L8 B- A- L16 A- L8 B-RB-B- L16 B- L8 B-RB-B- L16 B- L8 B-RB- L4 O6 D- O5 B- L8 B- A- L16 A- L8 B-RB-B-RB-RA-B-A-B-RB-B-A-B-A-A-A-B-A-G-A-B-A-G-G- L32 A-B-RA-B-RA-B-RA- L2 B- "
  //"O3 L4 E- L2 G- L8 E- L4 G- D- L2 F L8 D- L4 F <B L2 E- L8 <B L4 E- D- L2 F L8 D- L4 F"
  //"O5 L8 B- L4 A-B-A-B-A-B-A-B-A-B-A-B-A- L2 B- O4 L8 E- L4 FG-A-B- O5 D- O4 L2 B- L4 A- L8 G- L4 E-G- L2 A- L8 FE- L2 D- L8 R E- L4 FG-A-B- O5 D- O4 L2 B- R4 L8 A- L4 G-E-G- L1 A- L8 F E-D-"
  //"O4 L8 E- L4 FG-A-B- O5 D- O4 L2 B- L4 A- L8 G- L4 E-G- L2 A- L8 FE- L2 D- L8 R E- L4 FG-A-B- O5 D- O4 L2 B- R4 L8 A- L4 G-E-G- L1 A-");
}

void loop() {
  // put your main code here, to run repeatedly:

}
