model_name = 'lacy_lacz2';

% add one space before and after the species name
reaction = {...
   ' PLac + RNAP -> PLacRNAP ',...
   ' PLacRNAP -> PLac + RNAP ',...
   ' PLacRNAP -> TrLacZ1 ',...
   ' TrLacZ1 -> RbsLacZ + PLac + TrLacZ2 ',...
   ' TrLacZ2 -> TrLacY1 ',...
   ' TrLacY1 -> RbsLacY + TrLacY2 ',...
   ' TrLacY2 -> RNAP ',...
   ' Ribosome + RbsLacZ -> RbsribosomeLacZ ',...
   ' RbsribosomeLacZ -> Ribosome + RbsLacZ ',...
   ' Ribosome + RbsLacY -> RbsribosomeLacY ',...
   ' RbsribosomeLacY -> Ribosome + RbsLacY '...
   ' RbsribosomeLacZ -> TrRbsLacZ + RbsLacZ ',...
   ' RbsribosomeLacY -> TrRbsLacY + RbsLacY ',...
   ' TrRbsLacZ -> LacZ ',...
   ' TrRbsLacY -> LacY ',...
   ' LacZ -> dgrLacZ ',...
   ' LacY -> dgrLacY ',...
   ' RbsLacZ -> dgrRbsLacZ ',...
   ' RbsLacY -> dgrRbsLacY ',...
   ' LacZ + lactose -> LacZlactose ',...
   ' LacZlactose -> product + LacZ ',...
   ' LacY -> lactose + LacY '
};
   

rate = [ 0.17;
        10;
        1;
        1;
        0.015;
        1;
        0.36;
        0.17;
        0.45;
         0.17;
        0.45;
        0.4;
        0.4;
        0.015;
        0.036;
        6.42e-05;
        6.42e-05;
        0.3;
        0.3;
        9.52e-05;
        431;
        14; 
  ];


species={
   'PLac',...               % 1
   'RNAP',...               % 2
   'PLacRNAP',...           % 3
   'TrLacZ1',...            % 4
   'RbsLacZ',...            % 5
   'TrLacZ2',...            % 6
   'TrLacY1',...            % 7
   'RbsLacY',...            % 8
   'TrLacY2',...            % 9
   'Ribosome',...          % 10
   'RbsribosomeLacZ',...    % 11
   'RbsribosomeLacY',...    % 12
   'TrRbsLacZ',...          % 13
   'TrRbsLacY',...          % 14 
   'LacZ',...               % 15
   'LacY',...               % 16 
   'dgrLacZ',...            % 17 
   'dgrLacY',...            % 18
   'dgrRbsLacZ',...         % 19
   'dgrRbsLacY',...         % 20
   'lactose',...            % 21 grow very fast fast
   'LacZlactose',...        % 22 
   'product',...            % 23 grow very fast fast
   };



initial_pop=[
   1; ...
   350 ;...
   0; ...
   0; ...
   0; ...
   0; ...
   0; ...
   0; ...
   0; ...
   35;...
   0; ...
   0; ...
   0; ...
   0; ...
   0; ...
   0; ...
   0; ...
   0; ...
   0; ...
   0; ...
   0; ...
   0; ...
   0;
   ];

