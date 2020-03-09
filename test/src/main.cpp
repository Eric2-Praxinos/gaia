// CMakeProject1.cpp : définit le point d'entrée de l'application.
//

// #include <iostream>
#include "Gaia.h"

::nGaia::cRouter* MakeRoutes() {
	::nGaia::cRouter* router = new ::nGaia::cRouter();
	router->Push(::nGaia::cRoute());
	return router;
}

int main()
{
	::nGaia::cRouter* router = MakeRoutes();
	::nGaia::init(router); //give router and default route name, will open a Window containing this route
	
	/* 
		GaiaOptions options;
		options.Add("Category", "Option", 10);
		printf("%d\n", options.Get<int>("Category", "Option"));
		options.Set("Category", "Option", 20);
		printf("%d\n", options.Get<int>("Category", "Option"));
		options.Add<std::string>("MyButton", "label1", "str");

		std::string str = options.Get<std::string>("MyButton", "label");
		std::cout << str << std::endl;

		Application* application = gaia->CreateApplication(options);
	*/

	// wait
	int test;
	std::scanf("%d", &test);
	return 0;
}
