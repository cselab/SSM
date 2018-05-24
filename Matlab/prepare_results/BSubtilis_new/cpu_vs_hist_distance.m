clear; clc

eps = {'1.0',  '0.5',  '0.1', '0.05', '0.03', '0.01'};

load('SSA/hist.mat');
f_ssa=frq;
e_ssa=edges;

N = size(e_ssa,1);
M = size(e_ssa,2);

SpList = 1:M;
% % SpList = 14;

%% ========================================================================


col = get(groot,'DefaultAxesColorOrder');

err_t = zeros(1,length(eps));
err_t_a = zeros(1,length(eps));
err_r = zeros(1,length(eps));
err_s_a = zeros(1,length(eps));
err_s_v3 = zeros(1,length(eps));
err_s_v4 = zeros(1,length(eps));
err_s_v5 = zeros(1,length(eps));
eps_n = zeros(1,length(eps));

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
    
    load([ 'AdaptiveS/eps_' eps{k} '_hist.mat']);
    f_sleap_a=frq;
    e_sleap_a=edges;
    
    
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
            err_s_a(k)   = err_s_a(k)    +  h*sum( abs( f_sleap_a{i,Sp}  - f_ssa{i,Sp}) );
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
err_s_a = err_s_a/n/m;


%% timings

ssa=load('Timings/BSubtilis-SSA_times.txt');
s = ssa(1,2);
LB=3;
UB=6;

range=[1,4]

s1=load('Timings/BSubtilis-TauLeaping_times.txt');
s1 = s1(range,:);
s1(:,2)=s1(:,2)/s;

s1a=load('Timings/BSubtilis-AdaptiveTau_times.txt');
s1a = s1a(range,:);
s1a(:,2)=s1a(:,2)/s;

s2=load('Timings/BSubtilis-RLeaping_times.txt');
s2 = s2(range,:);
s2(:,2)=s2(:,2)/s;

s3=load('Timings/BSubtilis-SLeaping_v3_times.txt');
s3 = s3(range,:);
s3(:,2)=s3(:,2)/s;

%%
fig=figure(1); clf

set(groot,'defaulttextinterpreter','latex');  
set(groot, 'defaultAxesTickLabelInterpreter','latex');  
set(groot, 'defaultLegendInterpreter','latex'); 

% LB = 4;
% UB = 6;
hold on;grid on; axis tight

p=loglog(err_t(range), 1./s1(end:-1:1,2),'x-');
p.Color=[1 0 0];


p=loglog(err_r(range),1./s2(end:-1:1,2),'o-');
p.Color = [ 0.929, 0.694, 0.1250 ]; hold on


p=loglog(err_s_v3(range),1./s3(end:-1:1,2),'s-');
p.Color=[0 0 0];
set(findall(fig,'-property','FontSize'),'FontSize',20)

% axis([0.01,0.5, 0.055, 0.16])


ax = gca;
set(ax.Children, 'MarkerSize', 13)
set(ax.Children, 'LineWidth', 2)
ax.YLabel.String = 'speed up';
ax.XLabel.String = 'histogram distance';

% lh = legend('$\;$ $\tau$-leap','$\;$ ad. $\tau$-leap','$\;$ r-leap', ...
%             '$\;$ s-leap v3', '$\;$ s-leap v4','$\;$ s-leap v5','$\;$ ad. s-leap' );
lh = legend('$\;$ $\tau$-leap','$\;$ r-leap', ...
            '$\;$ s-leap' );
        
        
lh.FontSize = 20;
lh.Location='best';

set(gca,'GridLineStyle', '--','LineWidth',1.8);
set(gca,'GridAlpha',0.4);

box on;

%%


% saveas(gcf,'error_vs_time_bsubtilis', 'epsc' );






