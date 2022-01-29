int show_prime_numbers(int N){
    int prime_numbers[1'000'000];
    int prime_numbers_num = 0;
    if(N>1'000'000){
        cout << "N must be 1 < N < 1,000,000. The input value is" << N <<"." <<  endl;
        return -1;
    }
    
    prime_numbers[0] = 2;
    prime_numbers_num += 1;
    int tmp;
    for(int n=2; n<N; n++){
        for(int k=0; k<prime_numbers_num; k++){
            tmp = prime_numbers[k];
            if(n%tmp==0){
                break;
            }else if(k==prime_numbers_num-1){
                prime_numbers[prime_numbers_num]=n;
                prime_numbers_num+=1;
            }
        }
    }
    ofstream f;
    f.open("prime_numbers.txt", std::ios::out);
    for(int i=0; i<prime_numbers_num; i++){
        f << prime_numbers[i] << endl;
    }
    f.close();

    return prime_numbers_num;
}

%%time

show_prime_numbers(200000)


