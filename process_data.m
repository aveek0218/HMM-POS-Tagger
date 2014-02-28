[wtrn, ptrn] = process_data('treebank_train.txt');
[wtst, ptst] = process_data('treebank_test.txt');
save step1_result wtrn wtst ptrn ptst;
