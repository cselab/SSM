clear; clc

eps = { '1.0', '0.5', '0.1', '0.05', '0.03', '0.01'};

load('SSA/hist.mat');
f_ssa=frq;
e_ssa=edges;

N = size(e_ssa,1);
M = size(e_ssa,2);

SpList = 1:M;
% SpList = 14;

%% ========================================================================

col = get(groot,'DefaultAxesColorOrder');

err_t    = zeros(1,length(eps));
err_t_a  = zeros(1,length(eps));
err_r    = zeros(1,length(eps));
err_s_v3 = zeros(1,length(eps));
err_s_v4 = zeros(1,length(eps));
err_s_v5 = zeros(1,length(eps));
err_s_v6 = zeros(1,length(eps));
eps_n    = zeros(1,length(eps));

 for k = 1:length(eps)

    eps_n(k) = str2double(eps{k});
    
    
    load([ 'TauLeap/eps_' eps{k} '_hist.mat']);
    f_tleap=frq;
    e_tleap=edges;
    
    load([ 'AdaptiveTau/eps_' eps{k} '_hist.mat']);
    f_tleap_a = frq;
    e_tleap_a = edges;
    
    
    
    load([ 'RLeaping/eps_' eps{k} '_hist.mat']);
    f_rleap=frq;
    e_rleap=edges;
    
    
    
    load([ 'SLeaping_v3/eps_' eps{k} '_hist.mat']);
    f_sleap_v3=frq;
    e_sleap_v3=edges;
    
    
    load([ 'SLeaping_v4/eps_' eps{k} '_hist.mat']);
    f_sleap_v4=frq;
    e_sleap_v4=edges;

    load([ 'SLeaping_v5/eps_' eps{k} '_hist.mat']);
    f_sleap_v5=frq;
    e_sleap_v5=edges;
    
    load([ 'SLeaping_v6/eps_' eps{k} '_hist.mat']);
    f_sleap_v6=frq;
    e_sleap_v6=edges;
    
    
    list = 1:N;
    n = length(list);
    m = length(SpList);
    
    for i = list
        for Sp = SpList
            h = e_ssa{i,Sp}(2) - e_ssa{i,Sp}(1);
            err_t(k)     = err_t(k)      +  h*sum( abs( f_tleap{i,Sp}    - f_ssa{i,Sp}) );
            err_t_a(k)   = err_t_a(k)    +  h*sum( abs( f_tleap_a{i,Sp}  - f_ssa{i,Sp}) );
            err_r(k)     = err_r(k)      +  h*sum( abs( f_rleap{i,Sp}    - f_ssa{i,Sp}) );
            err_s_v3(k)  = err_s_v3(k)   +  h*sum( abs( f_sleap_v3{i,Sp} - f_ssa{i,Sp}) );
            err_s_v4(k)  = err_s_v4(k)   +  h*sum( abs( f_sleap_v4{i,Sp} - f_ssa{i,Sp}) );
            err_s_v5(k)  = err_s_v5(k)   +  h*sum( abs( f_sleap_v5{i,Sp} - f_ssa{i,Sp}) );
            err_s_v6(k)  = err_s_v6(k)   +  h*sum( abs( f_sleap_v6{i,Sp} - f_ssa{i,Sp}) );
        end
    end
    
    
    
 end

M = length(SpList);
err_t = err_t/n/m;
err_t_a = err_t_a/n/m;
err_r = err_r/n/m;
err_s_v3 = err_s_v3/n/m;
err_s_v4 = err_s_v4/n/m;
err_s_v5 = err_s_v5/n/m;
err_s_v6 = err_s_v6/n/m;
%%
fig=figure(1); clf
% fig.Position=[997 828 670 517];


set(groot,'defaulttextinterpreter','latex');  
set(groot, 'defaultAxesTickLabelInterpreter','latex');  
set(groot, 'defaultLegendInterpreter','latex'); 

p=loglog(eps_n,err_t,'x-');hold on
p.Color=[1 0 0];

% p=loglog(eps_n,err_t_a,'x--');hold on
% p.Color=[1 0 0];

grid on; axis tight

p=loglog(eps_n,err_r,'o-');
p.Color = [ 0.929, 0.694, 0.1250 ]; hold on


p=loglog(eps_n,err_s_v3,'s-');
p.Color=[0 0 0];
% p=loglog(eps_n,err_s_v4,'s-');
% p.Color=[0 0 0];
% p=loglog(eps_n,err_s_v5,'p-');
% p.Color=[0 0 0];
% p=loglog(eps_n,err_s_v6,'s--');
% p.Color=[0 0 0];



set(findall(fig,'-property','FontSize'),'FontSize',20)


ax = gca;
set(ax.Children, 'MarkerSize', 13)
set(ax.Children, 'LineWidth', 2)
ax.XLabel.String = '$\varepsilon$';
ax.YLabel.String = 'histogram distance';


lh = legend('$\;$ $\tau$-leap','$\;$ r-leap', '$\;$ s-leap' );

lh.FontSize = 20;
lh.Location='best';


%%


saveas(gcf,'error_lac_big', 'epsc' );






