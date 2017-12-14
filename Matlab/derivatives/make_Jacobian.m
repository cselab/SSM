clear

%% load the model
% run dimerization.m
run lacy_lacz.m

N = length(species);
M = length(reaction);


n=max( [ fix(abs(log10(abs(M))))+1  fix(abs(log10(abs(N))))+1 ] );
ID = @(i) sprintf(['%0' num2str(n) 'd'],i);

%% make a simbio model object with the original species name
model = sbiomodel(model_name);
for i=1:M
    r_obj  = addreaction(model, reaction{i});
    kl_obj = addkineticlaw(r_obj, 'MassAction');
    set( kl_obj, 'ParameterVariablenames', ['k' ID(i)] );
    p_obj  = addparameter(kl_obj, ['k' ID(i)], rate(i));    
end
sbmlexport(model, [model_name '.xml']);



%% rename species to X01, X02, ...


for i=1:N
    model.Species(i).rename([ ' X' ID(i) ] );
end



%% evaluate the Jacobian of the propensities

% for 2017b use str2sym and remove the suppress of the warning 
warning('off', 'symbolic:sym:sym:DeprecateExpressions' );

prop = cell(M,1);
for i=1:M
    prop{i} = sym( get(model.Reactions(i), 'ReactionRate') );
end

var = cell(N,1);
for i=1:N
    var{i} = sym([ 'X' ID(i) ]);
end


Jac = cell(M,N);
for i=1:M
    for j=1:N
        Jac{i,j} = diff(prop{i},var{j});
    end
end







%% evaluate the RHS

S = getstoichmatrix(model);

t=sym('t');

F = cell(N);
for i=1:N
    
    tmp = sym(0);
    for j=1:M
        tmp = tmp + S(i,j)*prop{j};
    end
    F{i} = var{i} - t*tmp;
    
end


%% evaluate the Jacobian of RHS

J = cell(N,N);
for i=1:N
    for j=1:N
        tmp = diff(F{i},var{j});
        J{i,j} = simplify(tmp);
    end
    
end





%% substitute variables in C format e.g., X1-->X[0]
J_s = cell(N,M);

for i=1:N
    for j=1:N
        J_s{i,j} = char(J{i,j});
    end
end

for i=1:N
    for j=1:N
        
        for k=1:N
            str_old = [ 'X' ID(k)  ];
            str_new = [ 'X[' num2str(k) ']' ];

            J_s{i,j} = strrep( J_s{i,j}, str_old, str_new );
        end
        
        for k=1:N
            str_old = [ 'k' ID(k) ];
            str_new = [ 'k[' num2str(k) ']' ];

            J_s{i,j} = strrep( J_s{i,j}, str_old, str_new );
        end
    end
end


%% write function in C format


cname = [ 'computeJacobian' model_name '.c'];
if( exist(cname,'file') )
    delete(cname);
end


fp = fopen( cname, 'w');

fprintf(fp,'/* \n');
fprintf(fp,'DESCRIPTION:  \n');
fprintf(fp,'Compute Jacobian for Decying Dimerization system in the implicit formula, \n');
fprintf(fp,'Implicit system: \n');
fprintf(fp,'X(t+tau) = X(t) + sum_j v_j * aj(X(t+tau))*tau + sum(..X(t)..) \n\n');

fprintf(fp,'Newton-Rapson is used to find roots of: \n');
fprintf(fp,'F  = X(t+tau) - sum_j v_j * aj(X(t+tau))*tau + B(X(t)) \n\n');
 
fprintf(fp,'where B is precmputed and is constant in Jacobian \n\n');
 
fprintf(fp,'Then blow is hardcoded Jacobian for F: \n');
fprintf(fp,'J = @F1/@X1  @F1/@X2  @F1/@X3  \n');
fprintf(fp,'    @F2/@X1  @F2/@X2  @F2/@X3 \n');
fprintf(fp,'    @F3/@X1  @F3/@X2  @F3/@X3 \n\n');

 fprintf(fp,'INPUT: \n');
 fprintf(fp,'Jacobian :  jacobian matrix stored as a vector\n');
 fprintf(fp,'X        :  vector systems sate X(t)\n');
 fprintf(fp,'rates    :  reaction rates\n');
 fprintf(fp,'tau      :  time step\n\n');
 
 fprintf(fp,'OUTPUT Jacobian: \n');
 fprintf(fp,'*/ \n\n\n');


 
 fprintf(fp,'void computeJacobianDimerization(vector<double>& J, vector<double> X, vector<double> k, double t ){ \n' );
 
 
 

for i=1:N
    for j=1:N
        t = ccode(sym(J_s{i,j})); t(1:6)=[];
        fprintf(fp,'J[%d][%d] = %s \n', i-1, j-1, t );
    end
    fprintf(fp,'\n');    
end

fprintf(fp,'\n\n');



fprintf(fp,'} \n\n');

fclose(fp);










