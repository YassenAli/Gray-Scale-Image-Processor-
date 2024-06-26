// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:			Gray Scale Image Processor
// Last Modification Date:	9/10/2023
// Author1 and ID and Group and Email:	Yassin Ali 20220381 s1 yassinalilearning77076@gmail.com
// Teaching Assistant:
// Purpose: Demonstrate use of bmplip for handling
//          bmp grayscale images
//          Program load a gray image and store in another file


#include <bits/stdc++.h> // Include all standard libraries
#include "bmplib.cpp"

using namespace std;

// Declare 2D arrays to hold the image data
unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];

//function to save processed image
void saveImage () {
    char imageFileName[100]; // Variable to hold the file name

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image); // Call function to write the image data to a BMP file
}

// Function to load an image for processing
void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image1);
}

// Function to load a second image for merging or another anything
void loadImage2 (char imageFileName[100]) {
    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);// Call function to read the BMP file into a 2D array
}

// Function to convert an image to black and white
void BW() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            if (image1[i][j] > 127) // If pixel value is greater than 127, set it to white
                image[i][j] = 255;
            else // Otherwise, set it to black
                image[i][j] = 0;
        }
}

// Function to invert an image's colors
void invert() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = 255 - image1[i][j]; // Subtract pixel value from 255 to invert it
}

// Function to merge two images together by averaging their pixel values
void merge() {
    cout<<"Please enter name of image file to merge with: ";
    char imageFileName[100]; cin >> imageFileName;
    loadImage2 (imageFileName);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = (image2[i][j] + image1[i][j]) / 2;
}

// Function to flip an image horizontally by reversing its rows
void flipHorizontally(){
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = image1[i][SIZE - j];
}

// Function to flip an image vertically by reversing its columns
void flipVertically(){
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = image1[SIZE - i][j];
}

// Function that prompts user whether they want to flip horizontally or vertically and calls corresponding function.
void flip() {
    cout<<"Flip (h)orizontally or (v)ertically ? ";
    char flip; cin>>flip;
    if(flip == 'h') flipHorizontally();
    else flipVertically();
}

// Function that darkens an image by reducing its pixel values by half.
void darken(){
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = 0.5 * image1[i][j];
}

// Function that lightens an image by increasing its pixel values by half.
void lighten(){
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (1.5 * image1[i][j] >= 255)
                image[i][j] = 255;
            else
                image[i][j] = 1.5 * image1[i][j];
}

// Function that prompts user whether they want to darken or lighten an image and calls corresponding function.
void DarkenLighten(){
    cout<<"Do you want to (d)arken or (l)ighten? ";
    char dark; cin>>dark;
    if(dark == 'd') darken();
    else lighten();
}

// Function that rotates an image 90 degrees clockwise.
void rotate90(){
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            image[j][SIZE-i] = image1[i][j];
}

// Function that rotates an image 180 degrees.
void rotate180(){
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            image[i][j] = image1[SIZE - i][SIZE - j];
}

// Function that rotates an image 270 degrees clockwise.
void rotate270(){
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            image[SIZE-j][i] = image1[i][j];
}

// Function that prompts user how many degrees they want to rotate an image and calls corresponding function.
void rotate(){
    cout<<"Rotate (90), (180) or (270) degrees?";
    int rotate; cin>>rotate;
    if (rotate == 90) rotate90();
    else if (rotate == 180) rotate180();
    else if (rotate == 270) rotate270();
}

// Function to detect edges in an image
void detect(){
    for (int i = 0; i < SIZE - 1; ++i)
        for (int j = 0; j < SIZE - 1; ++j) {
            // Check for vertical edge
            if (image1[i][j] - image1[i + 1][j] >= 30) image[i][j] = 0;
                // Check for horizontal edge
            else if (image1[i][j] - image1[i][j + 1] >= 30) image[i][j] = 0;
                // Check for diagonal edge
            else if (image1[i][j] - image1[i+1][j + 1] >= 30) image[i][j] = 0;
                // No edge detected
            else image[i][j] = 255;
        }
}

// Function to enlarge the first quarter of the image
void firstQuarter(){
    // Loop over the pixels and copy the corresponding pixel from the first quarter of the original image
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            image[i][j] = image1[i/2][j/2];
}

// Function to enlarge the second quarter of the image
void secondQuarter(){
    // Loop over the pixels and copy the corresponding pixel from the second quarter of the original image
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            image[i][j] = image1[i/2][SIZE/2 + j/2];
}

// Function to enlarge the third quarter of the image
void thirdQuarter(){
    // Loop over the pixels and copy the corresponding pixel from the third quarter of the original image
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            image[i][j] = image1[SIZE/2 + i/2][j/2];
}

// Function to enlarge the fourth quarter of the image
void fourthQuarter(){
    // Loop over the pixels and copy the corresponding pixel from the fourth quarter of the original image
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            image[i][j] = image1[SIZE/2 + i/2][SIZE/2 + j/2];
}

// Function to enlarge a specified quarter of the image
void enlarge(){
    cout<<"Which quarter to enlarge 1, 2, 3 or 4? : ";
    int enlarge; cin>>enlarge;
    if (enlarge == 1) firstQuarter();
    else if (enlarge == 2) secondQuarter();
    else if (enlarge == 3) thirdQuarter();
    else if (enlarge == 4) fourthQuarter();
}

// Function to shrink an image to half its size
void shrinkToHalf(){
    // Loop over the pixels and copy every second pixel from the original image
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if((i*2) <= 255 && (j*2) <= 255)
                image[i][j] = image1[i*2][j*2];
}

// Function to shrink an image to a third of its size
void shrinkToThird(){
    // Loop over the pixels and copy every third pixel from the original image
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if((i*3) <= 255 && (j*3) <= 255)
                image[i][j] = image1[i*3][j*3];
}

// Function to shrink an image to a fourth of its size
void shrinkToFourth(){
    // Loop over the pixels and copy every fourth pixel from the original image
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if((i*4) <= 255 && (j*4) <= 255)
                image[i][j] = image1[i*4][j*4];
}

// Function to shrink an image by a specified factor
void shrink(){
    cout<<"Shrink to 1 for (1/2), 2 for (1/3) or 3 for (1/4)? : ";
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            image[i][j] = 255;
    int shrink; cin>>shrink;
    if(shrink == 1) shrinkToHalf();
    else if (shrink == 2) shrinkToThird();
    else if (shrink == 3) shrinkToFourth();
}

// Function to mirror the lower half of the image to the upper half
void down(){
    for (int i = SIZE / 2; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            image[SIZE - i][j] = image1[i][j];
            image[i][j] = image1[i][j];
        }
}

// Function to mirror the upper half of the image to the lower half
void upper(){
    for (int i = 0; i < SIZE / 2; ++i)
        for (int j = 0; j < SIZE; ++j){
            image[SIZE - i][j] = image1[i][j];
            image[i][j] = image1[i][j];
        }
}

// Function to mirror the right half of the image to the left half
void right(){
    for (int i = 0; i < SIZE; ++i)
        for (int j = SIZE / 2; j < SIZE; ++j) {
            image[i][j] = image1[i][j];
            image[i][SIZE - j] = image1[i][j];
        }
}

// Function to mirror the left half of the image to the right half
void left(){
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE / 2; ++j){
            image[i][j] = image1[i][j];
            image[i][SIZE - j] = image1[i][j];
        }
}

// Function to mirror a specified side of the image
void mirror(){
    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side? : ";
    char mirror; cin>>mirror;
    if(mirror == 'd') down();
    else if (mirror == 'u') upper();
    else if (mirror == 'r') right();
    else if (mirror == 'l') left();
}

// Function to shuffle the quarters of an image
void shuffle(){
    // Create an array to represent the quarters of the image
    int quarters[4];

    // Get the order from the user
    cout << "Enter the order of the quarters (1-4): ";
    for (int i = 0; i < 4; ++i) {
        cin >> quarters[i];
        quarters[i]--; // Subtract 1 to get indices in the range 0-3
    }
    // Create a new image to hold the shuffled quarters
    unsigned char shuffled[SIZE][SIZE];

    // Copy the quarters from image1 to shuffled in the order specified by the quarters array
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int quarter = quarters[(i / (SIZE / 2)) * 2 + j / (SIZE / 2)];
            int x = (quarter / 2) * (SIZE / 2) + i % (SIZE / 2);
            int y = (quarter % 2) * (SIZE / 2) + j % (SIZE / 2);
            shuffled[i][j] = image1[x][y];
        }
    }


    // Copy the shuffled image back to image1
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = shuffled[i][j];
        }
    }
}
void blur(){
    // Apply the blur operation multiple times to increase the amount of blur
    for (int times = 0; times < 10; ++times) {
        for (int i = 1; i < SIZE - 1; ++i)
            for (int j = 1; j < SIZE - 1; ++j) {
                int sum = 0;
                for (int dx = -1; dx <= 1; ++dx)
                    for (int dy = -1; dy <= 1; ++dy)
                        sum += image1[i + dx][j + dy];
                image[i][j] = sum / 9;
            }
        // Copy the blurred image back to image1 for the next iteration
        if (times != 9)   // Skip the copy on the last iteration
            for (int i = 0; i < SIZE; ++i)
                for (int j = 0; j < SIZE; ++j)
                    image1[i][j] = image[i][j];
    }
}
// Function to crop a rectangular region from an image
void crop(){
    // Variables to hold the top-left corner (x, y) and the dimensions (l, w) of the rectangle
    int x, y, l, w;

    // Prompt the user to enter the top-left corner of the rectangle
    cout << "Enter the x position: "; cin >> x;
    cout << "Enter the y position: "; cin >> y;

    // Prompt the user to enter the dimensions of the rectangle
    cout << "Enter the length: "; cin >> l;
    cout << "Enter the width: "; cin >> w;

    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            // If the pixel is outside the rectangle, set it to white in image1
            if (i < x || i >= x + l || j < y || j >= y + w)
                image1[i][j] = 255;  // Set pixels outside the rectangle to white

            // Copy the pixel from image1 to image
            image[i][j] = image1[i][j];
        }
}
void skewHorizontally() {
    // Initialize a new image with all white pixels
    for(int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            image2[i][j] = 255;

    // Prompt the user to enter the degree of skew
    cout<<"Please enter degree to skew right or horizontally: ";
    float degree; cin>>degree;

    // Calculate the tangent of the skew angle
    float tanC = tan(degree * M_PI / 180.0); // Convert degree to radian and calculate tangent

    // Calculate the shrink factor
    float shrink_factor = 1 - tanC; // Shrink factor is 1 minus the tangent of the skew angle

    // Apply the shrink transformation to the original image and store the result in image2
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            int shrunken_x = x * shrink_factor; // Calculate the new x-coordinate after shrinking
            if (shrunken_x >= 0 && shrunken_x < SIZE) {
                image2[y][shrunken_x] = image1[y][x]; // Copy pixel from original image to new position in image2
            }
        }
    }

    // Apply the skew transformation to image2 and store the result in image
    for(int i = 0; i < SIZE; ++i) {
        int move =  (256-i) * tanC; // Calculate how much each row needs to be shifted for the skew
        for (int j = 0; j < SIZE; ++j)
            image[i][j+move] = image2[i][j]; // Copy pixel from image2 to new position in image after skewing
    }
}

void skewVertically(){
    float angle;
    cout<<"Please enter degree to skew up or vertically: ";
    cin >> angle;
    angle *= 22;
    angle /= 7;
    angle /= 180; // Convert angle from degree to radian

    float tanc = tan(angle); // Calculate tangent of angle
    float shrink = 1 - tanc; // Shrink factor is 1 minus the tangent of the skew angle

    for (int i=0; i<SIZE; i++)
        for (int j=0; j<SIZE; j++) {
            image2[i][j] = 255;
            image[i][j] = 255; // Initialize a new image with all white pixels
        }

    for (int i=0; i<SIZE; i++)
        for (int j=0; j<SIZE; j++) {
            int z = i * shrink; // Calculate the new y-coordinate after shrinking
            image2[z][j] = image1[i][j]; // Copy pixel from original image to new position in image2
        }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            int z = i + ((256-j) * tanc); // Calculate how much each column needs to be shifted for the skew
            if (z >= 0 && z < SIZE)
                image[z][j] = image2[i][j]; // Copy pixel from image2 to new position in image after skewing
        }
    }

    // Apply the skew transformation to image2 and store the result in image
    for(int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j){
            int move =  (256-j) * tanc;
            image[i+move][j] = image2[i][j];
        }
}
void applyFilter(char filter) {
    switch (filter) {
        case 's':
            saveImage(); // Save the processed image
            break;
        case '1':
            BW(); // Apply black and white filter
            break;
        case '2':
            invert();
            break;
        case '3':
            merge();
            break;
        case '4':
            flip();
            break;
        case '5':
            DarkenLighten();
            break;
        case '6':
            rotate();
            break;
        case '7':
            detect();
            break;
        case '8':
            enlarge();
            break;
        case '9':
            shrink();
            break;
        case 'a':
            mirror();
            break;
        case 'b':
            shuffle();
            break;
        case 'c':
            blur();
            break;
        case 'd':
            crop();
            break;
        case 'e':
            skewHorizontally();
            break;
        case 'f':
            skewVertically();
            break;
    }
}
void copyImage(){
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            image1[i][j] = image[i][j];
}
int main()
{
    cout<<"Ahlan ya user ya Habibi\n";

    loadImage();

    while(true) {
        cout << "Please select a filter number to apply or 0 to exit:\n"
                "1: Black & White\n"
                "2: Invert Image\n"
                "3: Merge Filter\n"
                "4: Flip Image\n"
                "5: Darken and Lighten Image\n"
                "6: Rotate Image\n"
                "7: Detect Image Edges\n"
                "8: Enlarge Image\n"
                "9: Shrink Image\n"
                "a: Mirror 1/2 Image\n"
                "b: Shuffle Image\n"
                "c: Blur Image\n"
                "d: Crop Image\n"
                "e: Skew Image Right or Horizontally\n"
                "f: Skew Image Up or Vertically\n"
                "s: Save the image to a file\n"
                "0: Exit\n";

        char filter; cin >> filter;
        if (filter == '0') {
            cout << "If you want to save the image Press s or e to exit\n";
            char save;
            cin >> save;
            if (save == 's') saveImage(); // Save the processed image
            return 0; //exit
        }
        applyFilter(filter);
        copyImage();// Copy processed image to 'image1' for further processing

    }
    return 0;
}
