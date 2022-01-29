%jsroot on

TCanvas *c = new TCanvas( "test" );
TH1 *frame = c->DrawFrame( 0.0, 0.0, 4.0, 10.0 );
double x[4] = { 0.0, 1.0, 2.0, 3.0 };
double y[4] = { 0.0, 1.0, 4.0, 9.0 };
TGraph *g = new TGraph( 4, x, y );
g->SetMarkerStyle( 20 ); 
g->SetMarkerSize( 1.0 );
g->Draw( "PC" );        // グラフを書く 
//c->Print( "test.png" ); // グラフをファイルに出力 

c->Draw();


