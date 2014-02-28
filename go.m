if isempty(which('histn')); mex histn.cpp; end
if isempty(which('textsplit')); mex textsplit.cpp; end
if isempty(which('log_sum')); mex log_sum.cpp; end

clear;
fprintf(1, 'Step1: processing input data...\n');
tic;
process_data;
toc;

clear;
fprintf(1, 'Step2: calculating probabilities\n');
tic;
calc_prob;
toc;

clear;
fprintf(1, 'Step3: doing viterbi\n');
tic;
viterbi;
toc;


fprintf(1, 'Viterbi accuracy: %f\n', (nnz(pitst_pred == pitst) / length(pitst)));

lPjoint = bsxfun(@plus, lPwt', lPt);
lPjoint = bsxfun(@minus, lPjoint, log_sum(lPjoint));
pitst_base = pitst;
[~, maxi] = max(lPjoint);
for i=1:length(pitst)
pitst_base(i) = maxi(witst(i));
end
fprintf(1, 'Baseline: %f\n', 1 - nnz(pitst_base ~= pitst) / length(pitst));
