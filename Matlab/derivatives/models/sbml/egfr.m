model_name = 'egfr';

% add one space before and after the species name
reaction = {...
'EGFR + EGF -> EGFxEGFR',...
'EGFxEGFR -> EGFR + EGF',...
'2 EGFxEGFR -> EGFxEGFR2',...
'EGFxEGFR2 -> 2 EGFxEGFR',...
'EGFxEGFR2 -> EGFxEGFR2xP',...
'EGFxEGFR2xP -> EGFxEGFR2',...
'EGFxEGFR2xP + PLCg -> EGFxEGFR2xPLCg',...
'EGFxEGFR2xPLCg -> EGFxEGFR2xP + PLCg',...
'EGFxEGFR2xPLCg -> EGFxEGFR2xPLCgxP',...
'EGFxEGFR2xPLCgxP -> EGFxEGFR2xPLCgxP',...
'EGFxEGFR2xPLCgxP -> PLCgxP + EGFxEGFR2xP',...
'PLCgxP + EGFxEGFR2xP -> EGFxEGFR2xPLCgxP',...
'PLCgxP -> PLCg',...
'Grb2 + EGFxEGFR2xP -> EGFxEGFR2xGrb2',...
'EGFxEGFR2xGrb2 -> Grb2 + EGFxEGFR2xP',...
'EGFxEGFR2xGrb2 + SOS -> EGFxEGFR2xGrb2xSOS',...
'EGFxEGFR2xGrb2xSOS -> EGFxEGFR2xGrb2 + SOS',...
'EGFxEGFR2xGrb2xSOS -> Grb2xSOS + EGFxEGFR2xP',...
'Grb2xSOS + EGFxEGFR2xP -> EGFxEGFR2xGrb2xSOS',...
'Grb2xSOS -> Grb2 + SOS',...
'Grb2 + SOS -> Grb2xSOS',...
'Shc + EGFxEGFR2xP -> EGFxEGFR2xShc',...
'EGFxEGFR2xShc -> Shc + EGFxEGFR2xP',...
'EGFxEGFR2xShc -> EGFxEGFRxShcxP',...
'EGFxEGFRxShcxP -> EGFxEGFR2xShc',...
'EGFxEGFRxShcxP -> EGFxEGFR2xP + ShcxP',...
'EGFxEGFR2xP + ShcxP -> EGFxEGFRxShcxP',...
'ShcxP -> Shc',...
'EGFxEGFRxShcxP + Grb2 -> EGFxEGFR2xShcxGrb2',...
'EGFxEGFR2xShcxGrb2 -> EGFxEGFRxShcxP + Grb2',...
'EGFxEGFR2xShcxGrb2 -> ShcxGrb2 + EGFxEGFR2xP',...
'ShcxGrb2 + EGFxEGFR2xP -> EGFxEGFR2xShcxGrb2',...
'SOS + EGFxEGFR2xShcxGrb2 -> EGFxEGFR2xShcxGrb2xSOS',...
'EGFxEGFR2xShcxGrb2xSOS -> SOS + EGFxEGFR2xShcxGrb2',...
'EGFxEGFR2xShcxGrb2xSOS -> ShcxGrb2xSOS + EGFxEGFR2xP',...
'ShcxGrb2xSOS + EGFxEGFR2xP -> EGFxEGFR2xShcxGrb2xSOS',...
'Grb2 + ShcxP -> ShcxGrb2',...
'ShcxGrb2 -> Grb2 + ShcxP',...
'ShcxGrb2 + SOS -> ShcxGrb2xSOS',...
'ShcxGrb2xSOS -> ShcxGrb2 + SOS',...
'ShcxGrb2xSOS -> Grb2xSOS + ShcxP',...
'Grb2xSOS + ShcxP -> ShcxGrb2xSOS',...
'EGFxEGFRxShcxP + Grb2xSOS -> EGFxEGFR2xShcxGrb2xSOS',...
'EGFxEGFR2xShcxGrb2xSOS -> EGFxEGFRxShcxP + Grb2xSOS',...
'PLCgxP -> PLCgPxI',...
'PLCgPxI -> PLCgxP'
};




rate = [
    0.0030;
    0.0600;
    0.0100;
    0.1000;
    1.0000;
  450.0000;
    0.0600;
    0.2000;
    1.0000;
    0.0500;
    0.3000;
    0.0060;
    1.0000;
    0.0030;
    0.0500;
    0.0100;
    0.0600;
    0.0300;
    0.0045;
    0.0015;
    0.0001;
    0.0900;
    0.6000;
    6.0000;
    0.0600;
    0.3000;
    0.0009;
    1.7000;
    0.0030;
    0.1000;
    0.3000;
    0.0009;
    0.0100;
    0.0214;
    0.1200;
    0.0002;
    0.0030;
    0.1000;
    0.0300;
    0.0640;
    0.1000;
    0.0210;
    0.0090;
    0.0429;
    1.0000;
    0.0300];


species = {
  'EGFR',...
  'EGF',...
  'EGFxEGFR',...
  'EGFxEGFR2',...
  'EGFxEGFR2xP',...
  'PLCg',...
  'EGFxEGFR2xPLCg',...
  'EGFxEGFR2xPLCgxP',...
  'PLCgxP',...
  'Grb2',...
  'EGFxEGFR2xGrb2',...
  'SOS',...
  'EGFxEGFR2xGrb2xSOS',...
  'Grb2xSOS',...
  'Shc',...
  'EGFxEGFR2xShc',...
  'EGFxEGFRxShcxP',...
  'ShcxP',...
  'EGFxEGFR2xShcxGrb2',...
  'ShcxGrb2',...
  'EGFxEGFR2xShcxGrb2xSOS',...
  'ShcxGrb2xSOS',...
  'PLCgPxI',...
  };



initial_pop=[
       0
     1
   581
    24
    28
     4
     1
     1
     1
     4
    15
     3
     2
     1
     2
     2
     1
     2
    82
     1
    36
     1
    30
   102
   ];






