// STL
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <memory>
// ROOT_CERN
#include <TApplication.h>
#include <TCanvas.h>
#include <TGraph.h>

const std::size_t							g_calc_num = 15;
std::vector<std::vector<long double> >		g_calc_list;
std::vector<std::vector<std::string> >		g_table;

int main(int argc, char * argv[])
{
	TApplication app("app", &argc, argv);

	double result;
	g_calc_list.resize(4);

	g_calc_list[0].push_back(0.994);
	for(auto i = 1lu; i < g_calc_num; ++i) {
		result = 1.0/2 * g_calc_list[0][i-1];
		g_calc_list[0].push_back(result);
	}//for

	g_calc_list[1].push_back(1);
	g_calc_list[1].push_back(0.497);
	for(auto i = 2lu; i < g_calc_num; ++i) {
		result = 3.0/2*g_calc_list[1][i-1] - 1.0/2*g_calc_list[1][i-2];
		g_calc_list[1].push_back(result);
	}//for

	g_calc_list[2].push_back(1);
	g_calc_list[2].push_back(0.497);
	for(auto i = 2lu; i < g_calc_num; ++i) {
		result = 5.0/2*g_calc_list[2][i-1] - g_calc_list[2][i-2];
		g_calc_list[2].push_back(result);
	}//for

	g_calc_list[3].push_back(1);
	for(auto i = 1lu; i < g_calc_num; ++i) {
		result = 1.0/2*g_calc_list[3][i-1];
		g_calc_list[3].push_back(result);
	}//for

	std::cout << "Sequence: " << std::endl;
	std::cout << std::setw(5) << "n"
		<< std::setw(18) << "rn"
		<< std::setw(18) << "pn"
		<< std::setw(18) << "qn"
		<< std::setw(18) << "xn" << std::endl;
	for(auto i = 0lu; i < g_calc_num; ++i) {
		std::cout.precision(10);
		std::cout.setf(std::ios_base::fixed);

		std::cout << std::setw(5) << i
			<< std::setw(18) << g_calc_list[0][i]
			<< std::setw(18) << g_calc_list[1][i]
			<< std::setw(18) << g_calc_list[2][i]
			<< std::setw(18) << g_calc_list[3][i] << std::endl;
	}//for
	std::cout << "==================================================" << std::endl;

	std::cout << "Error Sequence: " << std::endl;
	std::cout << std::setw(5) << "n"
		<< std::setw(18) << "xn-rn"
		<< std::setw(18) << "xn-pn"
		<< std::setw(18) << "xn-qn" << std::endl;
	for(auto i = 0lu; i < g_calc_num; ++i) {
		std::cout.precision(10);
		std::cout.setf(std::ios_base::fixed);

		std::cout << std::setw(5) << i
			<< std::setw(18) << g_calc_list[3][i] - g_calc_list[0][i]
			<< std::setw(18) << g_calc_list[3][i] - g_calc_list[1][i]
			<< std::setw(18) << g_calc_list[3][i] - g_calc_list[2][i] << std::endl;
	}//for

	const std::size_t win_w = 500;
	const std::size_t win_h = 500;
	std::shared_ptr<TCanvas> cc(new TCanvas("cc", "Graph", 100, 100, win_w, win_h));
	cc->Divide(1, 3);

	double diff_x[g_calc_num], diff_y[g_calc_num];
	for(auto i = 0lu; i < g_calc_num; ++i) {
		diff_x[i] = i;
		diff_y[i] = g_calc_list[3][i] - g_calc_list[0][i];
	}//for
	std::shared_ptr<TGraph> g1(new TGraph(g_calc_num, diff_x, diff_y));
	cc->cd(1);
	g1->Draw("A*");

	for(auto i = 0lu; i < g_calc_num; ++i)
		diff_y[i] = g_calc_list[3][i] - g_calc_list[1][i];
	std::shared_ptr<TGraph> g2(new TGraph(g_calc_num, diff_x, diff_y));
	cc->cd(2);
	g2->Draw("A*");

	for(auto i = 0lu; i < g_calc_num; ++i)
		diff_y[i] = g_calc_list[3][i] - g_calc_list[2][i];
	std::shared_ptr<TGraph> g3(new TGraph(g_calc_num, diff_x, diff_y));
	cc->cd(3);
	g3->Draw("A*");

	cc->SetEditable(kFALSE);
	cc->Update();
	cc->Show();

	app.Run();

	return 0;
}//main

