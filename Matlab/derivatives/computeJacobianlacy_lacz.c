/* 
DESCRIPTION:  
Compute Jacobian for Decying Dimerization system in the implicit formula, 
Implicit system: 
X(t+tau) = X(t) + sum_j v_j * aj(X(t+tau))*tau + sum(..X(t)..) 

Newton-Rapson is used to find roots of: 
F  = X(t+tau) - sum_j v_j * aj(X(t+tau))*tau + B(X(t)) 

where B is precmputed and is constant in Jacobian 

Then blow is hardcoded Jacobian for F: 
J = @F1/@X1  @F1/@X2  @F1/@X3  
    @F2/@X1  @F2/@X2  @F2/@X3 
    @F3/@X1  @F3/@X2  @F3/@X3 

INPUT: 
Jacobian :  jacobian matrix stored as a vector
X        :  vector systems sate X(t)
rates    :  reaction rates
tau      :  time step

OUTPUT Jacobian: 
*/ 


void computeJacobianDimerization(vector<double>& J, vector<double> X, vector<double> k, double t ){ 
J[0][0] =  t*X[1]*k[0]+1.0; 
J[0][1] =  t*X[0]*k[0]; 
J[0][2] =  -t*k[1]; 
J[0][3] =  -t*k[3]; 
J[0][4] =  0.0; 
J[0][5] =  0.0; 
J[0][6] =  0.0; 
J[0][7] =  0.0; 
J[0][8] =  0.0; 
J[0][9] =  0.0; 
J[0][10] =  0.0; 
J[0][11] =  0.0; 
J[0][12] =  0.0; 
J[0][13] =  0.0; 
J[0][14] =  0.0; 
J[0][15] =  0.0; 
J[0][16] =  0.0; 
J[0][17] =  0.0; 
J[0][18] =  0.0; 
J[0][19] =  0.0; 
J[0][20] =  0.0; 
J[0][21] =  0.0; 
J[0][22] =  0.0; 

J[1][0] =  t*X[1]*k[0]; 
J[1][1] =  t*X[0]*k[0]+1.0; 
J[1][2] =  -t*k[1]; 
J[1][3] =  0.0; 
J[1][4] =  0.0; 
J[1][5] =  0.0; 
J[1][6] =  -t*k[6]; 
J[1][7] =  0.0; 
J[1][8] =  0.0; 
J[1][9] =  0.0; 
J[1][10] =  0.0; 
J[1][11] =  0.0; 
J[1][12] =  0.0; 
J[1][13] =  0.0; 
J[1][14] =  0.0; 
J[1][15] =  0.0; 
J[1][16] =  0.0; 
J[1][17] =  0.0; 
J[1][18] =  0.0; 
J[1][19] =  0.0; 
J[1][20] =  0.0; 
J[1][21] =  0.0; 
J[1][22] =  0.0; 

J[2][0] =  -t*X[1]*k[0]; 
J[2][1] =  -t*X[0]*k[0]; 
J[2][2] =  t*(k[1]+k[2])+1.0; 
J[2][3] =  0.0; 
J[2][4] =  0.0; 
J[2][5] =  0.0; 
J[2][6] =  0.0; 
J[2][7] =  0.0; 
J[2][8] =  0.0; 
J[2][9] =  0.0; 
J[2][10] =  0.0; 
J[2][11] =  0.0; 
J[2][12] =  0.0; 
J[2][13] =  0.0; 
J[2][14] =  0.0; 
J[2][15] =  0.0; 
J[2][16] =  0.0; 
J[2][17] =  0.0; 
J[2][18] =  0.0; 
J[2][19] =  0.0; 
J[2][20] =  0.0; 
J[2][21] =  0.0; 
J[2][22] =  0.0; 

J[3][0] =  0.0; 
J[3][1] =  0.0; 
J[3][2] =  -t*k[2]; 
J[3][3] =  t*k[3]+1.0; 
J[3][4] =  0.0; 
J[3][5] =  0.0; 
J[3][6] =  0.0; 
J[3][7] =  0.0; 
J[3][8] =  0.0; 
J[3][9] =  0.0; 
J[3][10] =  0.0; 
J[3][11] =  0.0; 
J[3][12] =  0.0; 
J[3][13] =  0.0; 
J[3][14] =  0.0; 
J[3][15] =  0.0; 
J[3][16] =  0.0; 
J[3][17] =  0.0; 
J[3][18] =  0.0; 
J[3][19] =  0.0; 
J[3][20] =  0.0; 
J[3][21] =  0.0; 
J[3][22] =  0.0; 

J[4][0] =  0.0; 
J[4][1] =  0.0; 
J[4][2] =  0.0; 
J[4][3] =  -t*k[3]; 
J[4][4] =  t*(k[17]+k[18]+X[9]*k[7])+1.0; 
J[4][5] =  0.0; 
J[4][6] =  0.0; 
J[4][7] =  0.0; 
J[4][8] =  0.0; 
J[4][9] =  t*X[4]*k[7]; 
J[4][10] =  -t*(k[8]+k[11]); 
J[4][11] =  0.0; 
J[4][12] =  0.0; 
J[4][13] =  0.0; 
J[4][14] =  0.0; 
J[4][15] =  0.0; 
J[4][16] =  0.0; 
J[4][17] =  0.0; 
J[4][18] =  0.0; 
J[4][19] =  0.0; 
J[4][20] =  0.0; 
J[4][21] =  0.0; 
J[4][22] =  0.0; 

J[5][0] =  0.0; 
J[5][1] =  0.0; 
J[5][2] =  0.0; 
J[5][3] =  -t*k[3]; 
J[5][4] =  0.0; 
J[5][5] =  t*k[4]+1.0; 
J[5][6] =  0.0; 
J[5][7] =  0.0; 
J[5][8] =  0.0; 
J[5][9] =  0.0; 
J[5][10] =  0.0; 
J[5][11] =  0.0; 
J[5][12] =  0.0; 
J[5][13] =  0.0; 
J[5][14] =  0.0; 
J[5][15] =  0.0; 
J[5][16] =  0.0; 
J[5][17] =  0.0; 
J[5][18] =  0.0; 
J[5][19] =  0.0; 
J[5][20] =  0.0; 
J[5][21] =  0.0; 
J[5][22] =  0.0; 

J[6][0] =  0.0; 
J[6][1] =  0.0; 
J[6][2] =  0.0; 
J[6][3] =  0.0; 
J[6][4] =  0.0; 
J[6][5] =  -t*k[4]; 
J[6][6] =  t*k[6]+1.0; 
J[6][7] =  -t*k[5]; 
J[6][8] =  0.0; 
J[6][9] =  0.0; 
J[6][10] =  0.0; 
J[6][11] =  0.0; 
J[6][12] =  0.0; 
J[6][13] =  0.0; 
J[6][14] =  0.0; 
J[6][15] =  0.0; 
J[6][16] =  0.0; 
J[6][17] =  0.0; 
J[6][18] =  0.0; 
J[6][19] =  0.0; 
J[6][20] =  0.0; 
J[6][21] =  0.0; 
J[6][22] =  0.0; 

J[7][0] =  0.0; 
J[7][1] =  0.0; 
J[7][2] =  0.0; 
J[7][3] =  0.0; 
J[7][4] =  0.0; 
J[7][5] =  0.0; 
J[7][6] =  0.0; 
J[7][7] =  t*k[5]+1.0; 
J[7][8] =  0.0; 
J[7][9] =  0.0; 
J[7][10] =  0.0; 
J[7][11] =  0.0; 
J[7][12] =  0.0; 
J[7][13] =  0.0; 
J[7][14] =  0.0; 
J[7][15] =  0.0; 
J[7][16] =  0.0; 
J[7][17] =  0.0; 
J[7][18] =  0.0; 
J[7][19] =  0.0; 
J[7][20] =  0.0; 
J[7][21] =  0.0; 
J[7][22] =  0.0; 

J[8][0] =  0.0; 
J[8][1] =  0.0; 
J[8][2] =  0.0; 
J[8][3] =  0.0; 
J[8][4] =  0.0; 
J[8][5] =  0.0; 
J[8][6] =  0.0; 
J[8][7] =  -t*k[5]; 
J[8][8] =  t*X[9]*k[9]+1.0; 
J[8][9] =  t*X[8]*k[9]; 
J[8][10] =  0.0; 
J[8][11] =  -t*k[10]; 
J[8][12] =  0.0; 
J[8][13] =  -t*k[12]; 
J[8][14] =  0.0; 
J[8][15] =  0.0; 
J[8][16] =  0.0; 
J[8][17] =  0.0; 
J[8][18] =  0.0; 
J[8][19] =  0.0; 
J[8][20] =  0.0; 
J[8][21] =  0.0; 
J[8][22] =  0.0; 

J[9][0] =  0.0; 
J[9][1] =  0.0; 
J[9][2] =  0.0; 
J[9][3] =  0.0; 
J[9][4] =  t*X[9]*k[7]; 
J[9][5] =  0.0; 
J[9][6] =  0.0; 
J[9][7] =  0.0; 
J[9][8] =  t*X[9]*k[9]; 
J[9][9] =  t*(X[4]*k[7]+X[8]*k[9])+1.0; 
J[9][10] =  -t*k[8]; 
J[9][11] =  -t*k[10]; 
J[9][12] =  0.0; 
J[9][13] =  0.0; 
J[9][14] =  0.0; 
J[9][15] =  0.0; 
J[9][16] =  0.0; 
J[9][17] =  0.0; 
J[9][18] =  0.0; 
J[9][19] =  0.0; 
J[9][20] =  0.0; 
J[9][21] =  0.0; 
J[9][22] =  0.0; 

J[10][0] =  0.0; 
J[10][1] =  0.0; 
J[10][2] =  0.0; 
J[10][3] =  0.0; 
J[10][4] =  -t*X[9]*k[7]; 
J[10][5] =  0.0; 
J[10][6] =  0.0; 
J[10][7] =  0.0; 
J[10][8] =  0.0; 
J[10][9] =  -t*X[4]*k[7]; 
J[10][10] =  t*(k[8]+k[11])+1.0; 
J[10][11] =  0.0; 
J[10][12] =  0.0; 
J[10][13] =  0.0; 
J[10][14] =  0.0; 
J[10][15] =  0.0; 
J[10][16] =  0.0; 
J[10][17] =  0.0; 
J[10][18] =  0.0; 
J[10][19] =  0.0; 
J[10][20] =  0.0; 
J[10][21] =  0.0; 
J[10][22] =  0.0; 

J[11][0] =  0.0; 
J[11][1] =  0.0; 
J[11][2] =  0.0; 
J[11][3] =  0.0; 
J[11][4] =  0.0; 
J[11][5] =  0.0; 
J[11][6] =  0.0; 
J[11][7] =  0.0; 
J[11][8] =  -t*X[9]*k[9]; 
J[11][9] =  -t*X[8]*k[9]; 
J[11][10] =  0.0; 
J[11][11] =  t*k[10]+1.0; 
J[11][12] =  0.0; 
J[11][13] =  0.0; 
J[11][14] =  0.0; 
J[11][15] =  0.0; 
J[11][16] =  0.0; 
J[11][17] =  0.0; 
J[11][18] =  0.0; 
J[11][19] =  0.0; 
J[11][20] =  0.0; 
J[11][21] =  0.0; 
J[11][22] =  0.0; 

J[12][0] =  0.0; 
J[12][1] =  0.0; 
J[12][2] =  0.0; 
J[12][3] =  0.0; 
J[12][4] =  0.0; 
J[12][5] =  0.0; 
J[12][6] =  0.0; 
J[12][7] =  0.0; 
J[12][8] =  0.0; 
J[12][9] =  0.0; 
J[12][10] =  -t*k[11]; 
J[12][11] =  0.0; 
J[12][12] =  t*(k[13]+k[14])+1.0; 
J[12][13] =  0.0; 
J[12][14] =  0.0; 
J[12][15] =  0.0; 
J[12][16] =  0.0; 
J[12][17] =  0.0; 
J[12][18] =  0.0; 
J[12][19] =  0.0; 
J[12][20] =  0.0; 
J[12][21] =  0.0; 
J[12][22] =  0.0; 

J[13][0] =  0.0; 
J[13][1] =  0.0; 
J[13][2] =  0.0; 
J[13][3] =  0.0; 
J[13][4] =  0.0; 
J[13][5] =  0.0; 
J[13][6] =  0.0; 
J[13][7] =  0.0; 
J[13][8] =  0.0; 
J[13][9] =  0.0; 
J[13][10] =  0.0; 
J[13][11] =  0.0; 
J[13][12] =  0.0; 
J[13][13] =  t*k[12]+1.0; 
J[13][14] =  0.0; 
J[13][15] =  0.0; 
J[13][16] =  0.0; 
J[13][17] =  0.0; 
J[13][18] =  0.0; 
J[13][19] =  0.0; 
J[13][20] =  0.0; 
J[13][21] =  0.0; 
J[13][22] =  0.0; 

J[14][0] =  0.0; 
J[14][1] =  0.0; 
J[14][2] =  0.0; 
J[14][3] =  0.0; 
J[14][4] =  0.0; 
J[14][5] =  0.0; 
J[14][6] =  0.0; 
J[14][7] =  0.0; 
J[14][8] =  0.0; 
J[14][9] =  0.0; 
J[14][10] =  0.0; 
J[14][11] =  0.0; 
J[14][12] =  0.0; 
J[14][13] =  -t*k[12]; 
J[14][14] =  1.0; 
J[14][15] =  0.0; 
J[14][16] =  0.0; 
J[14][17] =  0.0; 
J[14][18] =  0.0; 
J[14][19] =  0.0; 
J[14][20] =  0.0; 
J[14][21] =  0.0; 
J[14][22] =  0.0; 

J[15][0] =  0.0; 
J[15][1] =  0.0; 
J[15][2] =  0.0; 
J[15][3] =  0.0; 
J[15][4] =  0.0; 
J[15][5] =  0.0; 
J[15][6] =  0.0; 
J[15][7] =  0.0; 
J[15][8] =  0.0; 
J[15][9] =  0.0; 
J[15][10] =  0.0; 
J[15][11] =  0.0; 
J[15][12] =  -t*k[13]; 
J[15][13] =  0.0; 
J[15][14] =  0.0; 
J[15][15] =  t*(k[15]+X[20]*k[19])+1.0; 
J[15][16] =  0.0; 
J[15][17] =  0.0; 
J[15][18] =  0.0; 
J[15][19] =  0.0; 
J[15][20] =  t*X[15]*k[19]; 
J[15][21] =  -t*k[20]; 
J[15][22] =  0.0; 

J[16][0] =  0.0; 
J[16][1] =  0.0; 
J[16][2] =  0.0; 
J[16][3] =  0.0; 
J[16][4] =  0.0; 
J[16][5] =  0.0; 
J[16][6] =  0.0; 
J[16][7] =  0.0; 
J[16][8] =  0.0; 
J[16][9] =  0.0; 
J[16][10] =  0.0; 
J[16][11] =  0.0; 
J[16][12] =  -t*k[14]; 
J[16][13] =  0.0; 
J[16][14] =  0.0; 
J[16][15] =  0.0; 
J[16][16] =  t*k[16]+1.0; 
J[16][17] =  0.0; 
J[16][18] =  0.0; 
J[16][19] =  0.0; 
J[16][20] =  0.0; 
J[16][21] =  0.0; 
J[16][22] =  0.0; 

J[17][0] =  0.0; 
J[17][1] =  0.0; 
J[17][2] =  0.0; 
J[17][3] =  0.0; 
J[17][4] =  0.0; 
J[17][5] =  0.0; 
J[17][6] =  0.0; 
J[17][7] =  0.0; 
J[17][8] =  0.0; 
J[17][9] =  0.0; 
J[17][10] =  0.0; 
J[17][11] =  0.0; 
J[17][12] =  0.0; 
J[17][13] =  0.0; 
J[17][14] =  0.0; 
J[17][15] =  -t*k[15]; 
J[17][16] =  0.0; 
J[17][17] =  1.0; 
J[17][18] =  0.0; 
J[17][19] =  0.0; 
J[17][20] =  0.0; 
J[17][21] =  0.0; 
J[17][22] =  0.0; 

J[18][0] =  0.0; 
J[18][1] =  0.0; 
J[18][2] =  0.0; 
J[18][3] =  0.0; 
J[18][4] =  -t*k[17]; 
J[18][5] =  0.0; 
J[18][6] =  0.0; 
J[18][7] =  0.0; 
J[18][8] =  0.0; 
J[18][9] =  0.0; 
J[18][10] =  0.0; 
J[18][11] =  0.0; 
J[18][12] =  0.0; 
J[18][13] =  0.0; 
J[18][14] =  0.0; 
J[18][15] =  0.0; 
J[18][16] =  -t*k[16]; 
J[18][17] =  0.0; 
J[18][18] =  1.0; 
J[18][19] =  0.0; 
J[18][20] =  0.0; 
J[18][21] =  0.0; 
J[18][22] =  0.0; 

J[19][0] =  0.0; 
J[19][1] =  0.0; 
J[19][2] =  0.0; 
J[19][3] =  0.0; 
J[19][4] =  -t*k[18]; 
J[19][5] =  0.0; 
J[19][6] =  0.0; 
J[19][7] =  0.0; 
J[19][8] =  0.0; 
J[19][9] =  0.0; 
J[19][10] =  0.0; 
J[19][11] =  0.0; 
J[19][12] =  0.0; 
J[19][13] =  0.0; 
J[19][14] =  0.0; 
J[19][15] =  0.0; 
J[19][16] =  0.0; 
J[19][17] =  0.0; 
J[19][18] =  0.0; 
J[19][19] =  1.0; 
J[19][20] =  0.0; 
J[19][21] =  0.0; 
J[19][22] =  0.0; 

J[20][0] =  0.0; 
J[20][1] =  0.0; 
J[20][2] =  0.0; 
J[20][3] =  0.0; 
J[20][4] =  0.0; 
J[20][5] =  0.0; 
J[20][6] =  0.0; 
J[20][7] =  0.0; 
J[20][8] =  0.0; 
J[20][9] =  0.0; 
J[20][10] =  0.0; 
J[20][11] =  0.0; 
J[20][12] =  0.0; 
J[20][13] =  0.0; 
J[20][14] =  0.0; 
J[20][15] =  t*X[20]*k[19]; 
J[20][16] =  -t*k[21]; 
J[20][17] =  0.0; 
J[20][18] =  0.0; 
J[20][19] =  0.0; 
J[20][20] =  t*X[15]*k[19]+1.0; 
J[20][21] =  0.0; 
J[20][22] =  0.0; 

J[21][0] =  0.0; 
J[21][1] =  0.0; 
J[21][2] =  0.0; 
J[21][3] =  0.0; 
J[21][4] =  0.0; 
J[21][5] =  0.0; 
J[21][6] =  0.0; 
J[21][7] =  0.0; 
J[21][8] =  0.0; 
J[21][9] =  0.0; 
J[21][10] =  0.0; 
J[21][11] =  0.0; 
J[21][12] =  0.0; 
J[21][13] =  0.0; 
J[21][14] =  0.0; 
J[21][15] =  -t*X[20]*k[19]; 
J[21][16] =  0.0; 
J[21][17] =  0.0; 
J[21][18] =  0.0; 
J[21][19] =  0.0; 
J[21][20] =  -t*X[15]*k[19]; 
J[21][21] =  t*k[20]+1.0; 
J[21][22] =  0.0; 

J[22][0] =  0.0; 
J[22][1] =  0.0; 
J[22][2] =  0.0; 
J[22][3] =  0.0; 
J[22][4] =  0.0; 
J[22][5] =  0.0; 
J[22][6] =  0.0; 
J[22][7] =  0.0; 
J[22][8] =  0.0; 
J[22][9] =  0.0; 
J[22][10] =  0.0; 
J[22][11] =  0.0; 
J[22][12] =  0.0; 
J[22][13] =  0.0; 
J[22][14] =  0.0; 
J[22][15] =  0.0; 
J[22][16] =  0.0; 
J[22][17] =  0.0; 
J[22][18] =  0.0; 
J[22][19] =  0.0; 
J[22][20] =  0.0; 
J[22][21] =  -t*k[20]; 
J[22][22] =  1.0; 



} 

