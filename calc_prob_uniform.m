load step1_result wtrn wtst ptrn ptst;

if ~exist('eta', 'var')
  eta = 0.01;
end

wmap = java.util.HashMap; wall = unique([wtrn; wtst]); 
pmap = java.util.HashMap; pall = unique([ptrn; ptst]);

for i=1:length(wall); wmap.put(wall{i}, i); end;
for i=1:length(pall); pmap.put(pall{i}, i); end;

% save step2_dictionary wmap pmap wall pall;

witrn = zeros(length(wtrn), 1); witst = zeros(length(wtst), 1);
pitrn = zeros(length(ptrn), 1); pitst = zeros(length(ptst), 1);

for i=1:length(wtrn); witrn(i) = wmap.get(wtrn{i}); end;
for i=1:length(wtst); witst(i) = wmap.get(wtst{i}); end;
for i=1:length(ptrn); pitrn(i) = pmap.get(ptrn{i}); end;
for i=1:length(ptst); pitst(i) = pmap.get(ptst{i}); end;

nw = length(wall); np = length(pall);

lPwt = zeros(nw, np);
lPtt = zeros(np, np);

pthis = pitrn(2:end);
plast = pitrn(1:end-1);

for i=1:np
  cnts_i = histn(witrn(pitrn == i), nw);
  lPwt(:, i) = log(max(eta, cnts_i));
  
  cnts_i = histn(pthis(plast == i), np);
  lPtt(:, i) = log(max(eta, cnts_i));
end

lPwt = bsxfun(@minus, lPwt, log_sum(lPwt));
lPtt = bsxfun(@minus, lPtt, log_sum(lPtt));

% Calculate the marginal state probability, used for the initial state.
lPt = repmat(-log(np), np, 1);
% lPt = bsxfun(@minus, lPt, log_sum(lPt));

% save step2_result lPwt lPtt lPt nw np witrn witst pitrn pitst;
