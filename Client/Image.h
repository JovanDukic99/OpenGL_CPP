class Image {
private:
	int width;
	int height;
	int** buffer;

public:
	Image(int width, int height);
	int* operator[](int index);
	void clear();
	int getWidth();
	int getHeight();

private:
	void init();
};