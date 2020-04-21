// CMakeProject1.cpp : définit le point d'entrée de l'application.
//

// #include <iostream>
#include "Gaia.h"
#include "Components/MyButton.h"
#include <conio.h>

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

	cMyButton myButton;
	//printf("Name = %s\n", component.Name().c_str());
	// printf("Height = %d\n", component.Height());

	while(1) {
		printf("=================================================\n");
		printf("Width = %d\n", myButton.mWidth.Value());
		printf("Height = %lf\n", myButton.mHeight.Value());
		printf("Length = %ld\n", myButton.mLength.Value());
		printf("Width * Height = %lf\n", myButton.mWidth * myButton.mHeight);
		printf("Area = %lf\n", myButton.mArea.Value());
		printf("Width * Height * Length = %lf\n", myButton.mWidth * myButton.mHeight * myButton.mLength);
		printf("Volume = %lf\n", myButton.mVolume.Value());
		printf("Width * Height == Area = %s\n", myButton.mWidth * myButton.mHeight == myButton.mArea ? "true" : "false");
		printf("Width * Height + 1 == Area = %s\n", myButton.mWidth * myButton.mHeight + 1 == myButton.mArea ? "true" : "false");


		wchar_t key = _getwch();
		if (key == 27) {
			break;
		}

		if (key == 0 || key == 224) {
			key = _getwch();
			switch(key) {
				case 72: //UP
					myButton.mHeight++;
				break;

				case 77: //RIGHT
					myButton.mWidth++;
				break;

				case 80: //DOWN
					myButton.mHeight--;
				break;

				case 75: //LEFT
					myButton.mWidth--;
				break;
			}
			continue;
		}
	}
	return 0;
}
