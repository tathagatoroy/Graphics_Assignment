# Assignment 1
This was an assignment in my Computer Graphics course where we had to create a 2D maze with a player whose objective was to collect coins ,avoid enemies and then reach the exit door while having positive health.
This project also contains some code from an earlier assignment which was an introductory one in openGL to render different composite shapes.



# The Shapes rendered
elongated square dipyramid 
undecagonal pyramid 
hexagonal dipyramid.

# Running instuction
Use Cmake and do the following 
'''
mkdir build
cd build
cmake ..
make ./Hello-World # if Hello-World is the name of the extracted folder
./Hello-World 

'''



# KEYS 
W : move up
A : move left
S : move down
D : move right
Q : quit
T: Teleport to a random position

# NOTES
1.The Text rendering is done in freetype I have used the code from 
https://learnopengl.com/code_viewer_gh.php?code=src/7.in_practice/2.text_rendering/text_rendering.cpp

NOTE: The text rendering part is not original code 

2.The Font uses absolute path,so you need to modify it if you are running in your computer
It is main.cpp
