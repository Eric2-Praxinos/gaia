// CMakeProject1.cpp : définit le point d'entrée de l'application.
//

// #include <iostream>
#include "Gaia.h"
#include "Components/MyHouse.h"
#include <conio.h>
#include <iostream>

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
		options.Add<std::string>("MyHouse", "label1", "str");

		std::string str = options.Get<std::string>("MyHouse", "label");
		std::cout << str << std::endl;

		Application* application = gaia->CreateApplication(options);
	*/

	cMyHouse myHouse;
	//printf("Name = %s\n", component.Name().c_str());
	// printf("Height = %d\n", component.Height());

	while(1) {
		printf("=================================================\n");
		printf("Width = %d\n", myHouse.mWidth());
		printf("Height = %lf\n", myHouse.mHeight());
		printf("Length = %ld\n", myHouse.mLength());
		printf("Width * Height = %lf\n", myHouse.mWidth * myHouse.mHeight);
		printf("Area = %lf\n", myHouse.mArea());
		printf("Width * Height * Length = %lf\n", myHouse.mWidth * myHouse.mHeight * myHouse.mLength);
		printf("Volume = %lf\n", myHouse.mVolume());
		printf("Width * Height == Area = %s\n", myHouse.mWidth * myHouse.mHeight == myHouse.mArea ? "true" : "false");
		printf("Width * Height + 1 == Area = %s\n", myHouse.mWidth * myHouse.mHeight + 1 == myHouse.mArea ? "true" : "false");


		wchar_t key = _getwch();
		if (key == 27) {
			break;
		}

		if (key == 0 || key == 224) {
			key = _getwch();
			EDIT(myHouse.mWidth, myHouse.mHeight) AS(w, h)
			{
				switch(key)
				{
					case 72: {
						h++;
					}
					break;

					case 77: //RIGHT
						w++;
					break;

					case 80: //DOWN
						h--;
					break;

					case 75: //LEFT
						w--;
					break;
				}
				continue;
			}
		}
	}
	return 0;
}
