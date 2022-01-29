!pwd

int show_prime_numbers(int N){
    int prime_numbers[1'000'000];
    int prime_numbers_num = 0;
    if(N>1'000'000){
        cout << "N must be 1 < N < 1,000,000. The input value is" << N <<"." <<  endl;
        return -1;
    }
    
    prime_numbers[0] = 2;
    prime_numbers_num += 1;
    for(int n=2; n<N; n++){
        for(int k=2; k<n; k++){
            if(n%k==0){
                break;
            }else if(k==n-1){
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
show_prime_numbers(100)

%%time
show_prime_numbers(500)

%%time
show_prime_numbers(1000)

%%time
show_prime_numbers(5000)

%%time
show_prime_numbers(20000)

%%time
show_prime_numbers(100000)

%%time
show_prime_numbers(200000)

%%time
show_prime_numbers(500000)

TCanvas* c0 = new TCanvas("canvas0", "Prime number calculation time", 600, 400);
double N[8] = {100, 500, 1000, 5000, 20000, 100000, 200000, 500000};
double t[8] = {0.20, 0.20, 0.20, 0.26, 0.58, 3.10, 8.68, 41.21};
TGraph* graph = new TGraph(8, N, t);
graph->Draw("AC*");

c0->Draw();

%jsroot

c0->Draw();


