clear; clc


eps = {'0.01', '0.03', '0.05'};

load('SSA/hist.mat');
f_ssa=frq;
e_ssa=edges;

N = size(e_ssa,1);
M = size(e_ssa,2);

SpList = [6 13 14];
% SpList = 6;

%% ========================================================================


col = get(groot,'DefaultAxesColorOrder');

err_t = zeros(1,length(eps));
err_t_a = zeros(1,length(eps));
err_r = zeros(1,length(eps));
err_s_a = zeros(1,length(eps));
err_s_v1 = zeros(1,length(eps));
err_s_v2 = zeros(1,length(eps));
err_s_v3 = zeros(1,length(eps));
err_s_v4 = zeros(1,length(eps));
eps_n = zeros(1,length(eps));

 for k = 1:length(eps)

    eps_n(k) = str2double(eps{k});
    
    load([ 'AdaptiveTau/eps_' eps{k} '_hist.mat']);
    f_tleap_a = frq;
    e_tleap_a = edges;
    
    load([ 'TauLeaping/eps_' eps{k} '_hist.mat']);
    f_tleap=frq;
    e_tleap=edges;
    
    
    load([ 'RLeapingJana/eps_' eps{k} '_hist.mat']);
    f_rleap=frq;
    e_rleap=edges;
    
    
    

    load([ 'AdaptiveS/eps_' eps{k} '_hist.mat']);
    f_sleap_a=frq;
    e_sleap_a=edges;
    
    load([ 'SLeaping_v1/eps_' eps{k} '_hist.mat']);
    f_sleap_v1=frq;
    e_sleap_v1=edges;

    load([ 'SLeaping_v2/eps_' eps{k} '_hist.mat']);
    f_sleap_v2=frq;
    e_sleap_v2=edges;
    
    load([ 'SLeaping_v3/eps_' eps{k} '_hist.mat']);
    f_sleap_v3=frq;
    e_sleap_v3=edges;
    
    load([ 'SLeaping_v4/eps_' eps{k} '_hist.mat']);
    f_sleap_v4=frq;
    e_sleap_v4=edges;
    
    
    
    
    
    for i = 2:N-1
        for Sp = SpList
            h = e_ssa{i,Sp}(2) - e_ssa{i,Sp}(1);
            err_t(k) = err_t(k) + h*sum( abs(f_tleap{i,Sp}-f_ssa{i,Sp}) );
            err_t_a(k) = err_t_a(k) + h*sum( abs(f_tleap_a{i,Sp}-f_ssa{i,Sp}) );
            err_r(k) = err_r(k) + h*sum( abs(f_rleap{i,Sp}-f_ssa{i,Sp}) );
            err_s_a(k) = err_s_a(k) + h*sum( abs(f_sleap_a{i,Sp}-f_ssa{i,Sp}) );
            err_s_v1(k) = err_s_v1(k) + h*sum( abs(f_sleap_v1{i,Sp}-f_ssa{i,Sp}) );
            err_s_v2(k) = err_s_v2(k) + h*sum( abs(f_sleap_v2{i,Sp}-f_ssa{i,Sp}) );
            err_s_v3(k) = err_s_v3(k) + h*sum( abs(f_sleap_v3{i,Sp}-f_ssa{i,Sp}) );
            err_s_v4(k) = err_s_v4(k) + h*sum( abs(f_sleap_v4{i,Sp}-f_ssa{i,Sp}) );
        end
    end
    
    
    
 end

M = length(SpList);
err_t = err_t/(N-2)/M;
err_t_a = err_t_a/(N-2)/M;
err_r = err_r/(N-2)/M;
err_s_a = err_s_a/(N-2)/M;
err_s_v1 = err_s_v1/(N-2)/M;
err_s_v2 = err_s_v2/(N-2)/M;
err_s_v3 = err_s_v3/(N-2)/M;
err_s_v4 = err_s_v4/(N-2)/M;
%%
fig=figure(1); clf

set(groot,'defaulttextinterpreter','latex');  
set(groot, 'defaultAxesTickLabelInterpreter','latex');  
set(groot, 'defaultLegendInterpreter','latex'); 

p=loglog(eps_n,err_t_a,'x--');hold on
p.Color=[1 0 0];

p=loglog(eps_n,err_t,'x-');hold on
p.Color=[1 0 0];


grid on; axis tight

p=loglog(eps_n,err_r,'o-');
p.Color = [ 0.929, 0.694, 0.1250 ];


p=loglog(eps_n,err_s_a,'s--');
p.Color=[0 0 0];

p=loglog(eps_n,err_s_v1,'d-');
p.Color=[0 0 0];
p=loglog(eps_n,err_s_v2,'p-');
p.Color=[0 0 0];
p=loglog(eps_n,err_s_v3,'h-');
p.Color=[0 0 0];
p=loglog(eps_n,err_s_v4,'s-');
p.Color=[0 0 0];


set(findall(fig,'-property','FontSize'),'FontSize',20)


ax = gca;
set(ax.Children, 'MarkerSize', 13)
set(ax.Children, 'LineWidth', 2)
ax.XLabel.String = '$\varepsilon$';
ax.YLabel.String = 'histogram distance';


lh = legend('$\;$ ad. $\tau$-leap','$\;$ $\tau$-leap','$\;$ r-leap','$\;$ ad. s-leap',...
            '$\;$ s-leap v1','$\;$ s-leap v2','$\;$ s-leap v3','$\;$ s-leap v4');

lh.FontSize = 20;
lh.Location='best';


%%


saveas(gcf,'error_lac_dim', 'epsc' );







