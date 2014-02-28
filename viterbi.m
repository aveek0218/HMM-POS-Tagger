load step2_result lPwt lPtt lPt nw np witrn witst pitrn pitst;

pitst_pred = viterbi(lPtt, lPwt, lPt, witst);


