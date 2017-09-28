#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void extract_star(char* star_image, int index, int x, int y, int width, int height){

	star_image[index] = '0';

	// Check if at west border
	if(!(x - 1 < 0)){
		if(star_image[index-1] == '-'){
			extract_star(star_image, index - 1, x-1, y, width, height);
		}
	}
	
	// Check if at east border
	if(x + 1 < width){
		if(star_image[index+1] == '-'){
			extract_star(star_image, index + 1, x+1, y, width, height);
		}
	}

	// Check if at north border
	if(!(y - 1 < 0)){
		if(star_image[index - width] == '-'){
			extract_star(star_image, index - width, x, y-1, width, height);
		}
	}

	// Check if at south border
	if(y + 1 < height){
		if(star_image[index + width] == '-'){
			extract_star(star_image, index + width, x, y+1, width, height);
		}
	}

	return;
}

void print_map(char* star_image, int m, int n){
	// Print Star Image
	for(int y = 0; y<m; y++){
		for(int x = 0; x<n; x++){
			cout << star_image[n*y+x];
		}
		cout << endl;
	}
	return;
}

int main(){
	int m = 0;
	int n = 0;
	int num_stars[50] = {0};
	int num_cases = -1;

	// 1 < m,n < 100
	// max is 100 * 100
	char* star_image = new char[10000];

	while(cin >> m >> n){

		num_cases++;
		num_stars[num_cases] = 0;

		// Get Image
		for(int y = 0; y<m; y++){
			for(int x = 0; x<n; x++){
				cin >> star_image[y*n+x];
			}
		}

		print_map(star_image,m,n);

		// Extract Stars
		for(int y = 0; y<m; y++){
			for(int x = 0; x<n; x++){
				if(star_image[n * y + x] == '-'){
					extract_star(star_image, n * y + x, x, y, n, m);
					num_stars[num_cases]++;
					print_map(star_image, m, n);
				}
			}
		}	
	}

	for(int i = 0; i < num_cases+1; i++){
		cout << "Case " << i+1 << ": " << num_stars[i] << endl;
	}

	delete[] star_image;

	return 0;
}