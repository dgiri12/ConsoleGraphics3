//Transfer data into screen variable
//for (int j = 0; j < screenHeight; j++)
//{
//	for (int i = 0; i < screenWidth; i++)
//	{
//		char chTemp = rand() % 100 + 1; string stTmp(1, chTemp);
//		screen.replace(j*screenWidth + i, 1, stTmp);
//	}
//}

//char ch1 = 32/*space*/, ch2 = 65/*"A"*/;
//string s1(1, ch1); string s2(1, ch2);
//string rawString = _image;
//string outputString = "";
//string str = "";
//for (int i = 0; i < _width*_height; i++)
//{
//	str = rawString.substr(i, 1);
//	if (str == s1 && str == s2)
//	{
//		outputString += str;
//	}
//}
//image = outputString;

//void putSprite(int _x, int _y)
//{
//	int imagePos = 0;
//	for (int j = _y; j < _y + height; j++)
//	{
//		for (int i = _x; i < _x + width; i++)
//		{
//			//screen.replace(j*screenWidth + i, 1, image.substr(imagePos,1));
//			screen.replace(33 + i, 1, image.substr(imagePos, 1));
//			imagePos++;
//		}
//	}
//}

//char ch1 = 32/*space*/, ch2 = 65/*A*/;
//string s1(1, ch1); string s2(1, ch2);
//string str = "";
//for (int i = 0; i < outputString.length(); i++)
//{
//	str = outputString.substr(i, 1);
//	if (str == s1 || str == s2)
//	{
//		outputString.replace(i, 1, "");
//		i--; //When these characters are consecutive, it skips iterating
//			 //so bring it back
//	}
//}

//This code makes it that holding down space fires weapon at certain interval
