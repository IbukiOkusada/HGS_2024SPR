xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 88;
 0.66697;-1.09690;-4.22925;,
 -7.11669;-1.09690;-7.41070;,
 -7.11669;1.16025;-7.41070;,
 0.66697;1.16025;-4.22925;,
 -16.72393;-1.09690;-9.18457;,
 -16.72393;1.16025;-9.18457;,
 -24.46935;-1.09690;-6.41760;,
 -24.46935;1.16025;-6.41760;,
 -27.39140;-1.09690;0.30475;,
 -27.39140;1.16025;0.30475;,
 -24.38315;-1.09690;6.98895;,
 -24.38315;1.16025;6.98895;,
 -16.60283;-1.09690;9.65613;,
 -16.60283;1.16025;9.65613;,
 -7.01919;-1.09690;7.75890;,
 -7.01919;1.16025;7.75890;,
 0.72294;-1.09690;4.47763;,
 0.72294;1.16025;4.47763;,
 3.66012;-1.09690;0.10515;,
 3.66012;1.16025;0.10515;,
 0.66697;-1.09690;-4.22925;,
 0.66697;1.16025;-4.22925;,
 -7.11669;-1.09690;-7.41070;,
 0.66697;-1.09690;-4.22925;,
 -11.86566;-1.09690;0.20495;,
 -16.72393;-1.09690;-9.18457;,
 -24.46935;-1.09690;-6.41760;,
 -27.39140;-1.09690;0.30475;,
 -24.38315;-1.09690;6.98895;,
 -16.60283;-1.09690;9.65613;,
 -7.01919;-1.09690;7.75890;,
 0.72294;-1.09690;4.47763;,
 3.66012;-1.09690;0.10515;,
 0.66697;1.16025;-4.22925;,
 -7.11669;1.16025;-7.41070;,
 -11.86566;1.16025;0.20495;,
 -16.72393;1.16025;-9.18457;,
 -24.46935;1.16025;-6.41760;,
 -27.39140;1.16025;0.30475;,
 -24.38315;1.16025;6.98895;,
 -16.60283;1.16025;9.65613;,
 -7.01919;1.16025;7.75890;,
 0.72294;1.16025;4.47763;,
 3.66012;1.16025;0.10515;,
 -1.83413;-1.09690;5.63880;,
 -6.94324;-1.09690;6.60330;,
 -6.94324;1.16025;6.60330;,
 -1.83413;1.16025;5.63880;,
 -12.72749;-1.09690;8.96993;,
 -12.72749;1.16025;8.96993;,
 -16.37350;-1.09690;13.17065;,
 -16.37350;1.16025;13.17065;,
 -16.37271;-1.09690;17.85748;,
 -16.37271;1.16025;17.85748;,
 -13.07606;-1.09690;20.46448;,
 -13.07606;1.16025;20.46448;,
 -8.09344;-1.09690;19.22015;,
 -8.09344;1.16025;19.22015;,
 -3.21213;-1.09690;14.85631;,
 -3.21213;1.16025;14.85631;,
 0.30742;-1.09690;10.37578;,
 0.30742;1.16025;10.37578;,
 0.88457;-1.09690;6.96738;,
 0.88457;1.16025;6.96738;,
 -1.83413;-1.09690;5.63880;,
 -1.83413;1.16025;5.63880;,
 -6.94324;-1.09690;6.60330;,
 -1.83413;-1.09690;5.63880;,
 -7.74406;-1.09690;12.41243;,
 -12.72749;-1.09690;8.96993;,
 -16.37350;-1.09690;13.17065;,
 -16.37271;-1.09690;17.85748;,
 -13.07606;-1.09690;20.46448;,
 -8.09344;-1.09690;19.22015;,
 -3.21213;-1.09690;14.85631;,
 0.30742;-1.09690;10.37578;,
 0.88457;-1.09690;6.96738;,
 -1.83413;1.16025;5.63880;,
 -6.94324;1.16025;6.60330;,
 -7.74406;1.16025;12.41243;,
 -12.72749;1.16025;8.96993;,
 -16.37350;1.16025;13.17065;,
 -16.37271;1.16025;17.85748;,
 -13.07606;1.16025;20.46448;,
 -8.09344;1.16025;19.22015;,
 -3.21213;1.16025;14.85631;,
 0.30742;1.16025;10.37578;,
 0.88457;1.16025;6.96738;;
 
 60;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 3;22,23,24;,
 3;25,22,24;,
 3;26,25,24;,
 3;27,26,24;,
 3;28,27,24;,
 3;29,28,24;,
 3;30,29,24;,
 3;31,30,24;,
 3;32,31,24;,
 3;23,32,24;,
 3;33,34,35;,
 3;34,36,35;,
 3;36,37,35;,
 3;37,38,35;,
 3;38,39,35;,
 3;39,40,35;,
 3;40,41,35;,
 3;41,42,35;,
 3;42,43,35;,
 3;43,33,35;,
 4;44,45,46,47;,
 4;45,48,49,46;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 3;66,67,68;,
 3;69,66,68;,
 3;70,69,68;,
 3;71,70,68;,
 3;72,71,68;,
 3;73,72,68;,
 3;74,73,68;,
 3;75,74,68;,
 3;76,75,68;,
 3;67,76,68;,
 3;77,78,79;,
 3;78,80,79;,
 3;80,81,79;,
 3;81,82,79;,
 3;82,83,79;,
 3;83,84,79;,
 3;84,85,79;,
 3;85,86,79;,
 3;86,87,79;,
 3;87,77,79;;
 
 MeshMaterialList {
  5;
  60;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    ".png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.016000;0.016000;0.016000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  24;
  0.626633;0.000000;-0.779315;,
  0.281444;0.000000;-0.959578;,
  -0.080177;0.000000;-0.996781;,
  -0.683053;0.000000;-0.730369;,
  -0.999979;0.000000;0.006430;,
  -0.673606;0.000000;0.739091;,
  -0.067358;0.000000;0.997729;,
  0.293757;0.000000;0.955880;,
  0.636599;0.000000;0.771195;,
  0.830101;0.000000;0.557613;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.133582;0.000000;-0.991038;,
  -0.283534;0.000000;-0.958962;,
  -0.582801;0.000000;-0.812615;,
  -0.936835;0.000000;-0.349770;,
  -0.900043;0.000000;0.435802;,
  -0.210602;0.000000;0.977572;,
  0.468071;0.000000;0.883691;,
  0.729244;0.000000;0.684254;,
  0.914391;0.000000;0.404832;,
  0.985965;0.000000;0.166955;,
  0.822866;0.000000;-0.568236;,
  0.439059;0.000000;-0.898458;;
  60;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;22,0,0,22;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;23,12,12,23;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;;
 }
 MeshTextureCoords {
  88;
  0.375000;0.687500;,
  0.400000;0.687500;,
  0.400000;0.311560;,
  0.375000;0.311560;,
  0.425000;0.687500;,
  0.425000;0.311560;,
  0.450000;0.687500;,
  0.450000;0.311560;,
  0.475000;0.687500;,
  0.475000;0.311560;,
  0.500000;0.687500;,
  0.500000;0.311560;,
  0.525000;0.687500;,
  0.525000;0.311560;,
  0.550000;0.687500;,
  0.550000;0.311560;,
  0.575000;0.687500;,
  0.575000;0.311560;,
  0.600000;0.687500;,
  0.600000;0.311560;,
  0.625000;0.687500;,
  0.625000;0.311560;,
  0.548284;0.992353;,
  0.626409;0.935591;,
  0.500000;0.850000;,
  0.451716;0.992353;,
  0.373591;0.935591;,
  0.343750;0.843750;,
  0.373591;0.751909;,
  0.451716;0.695147;,
  0.548284;0.695147;,
  0.626409;0.751909;,
  0.656250;0.843750;,
  0.626409;0.064409;,
  0.548284;0.007647;,
  0.500000;0.162500;,
  0.451716;0.007647;,
  0.373591;0.064409;,
  0.343750;0.156250;,
  0.373591;0.248091;,
  0.451716;0.304853;,
  0.548284;0.304853;,
  0.626409;0.248091;,
  0.656250;0.156250;,
  0.375000;0.687500;,
  0.400000;0.687500;,
  0.400000;0.311560;,
  0.375000;0.311560;,
  0.425000;0.687500;,
  0.425000;0.311560;,
  0.450000;0.687500;,
  0.450000;0.311560;,
  0.475000;0.687500;,
  0.475000;0.311560;,
  0.500000;0.687500;,
  0.500000;0.311560;,
  0.525000;0.687500;,
  0.525000;0.311560;,
  0.550000;0.687500;,
  0.550000;0.311560;,
  0.575000;0.687500;,
  0.575000;0.311560;,
  0.600000;0.687500;,
  0.600000;0.311560;,
  0.625000;0.687500;,
  0.625000;0.311560;,
  0.548284;0.992353;,
  0.626409;0.935591;,
  0.500000;0.850000;,
  0.451716;0.992353;,
  0.373591;0.935591;,
  0.343750;0.843750;,
  0.373591;0.751909;,
  0.451716;0.695147;,
  0.548284;0.695147;,
  0.626409;0.751909;,
  0.656250;0.843750;,
  0.626409;0.064409;,
  0.548284;0.007647;,
  0.500000;0.162500;,
  0.451716;0.007647;,
  0.373591;0.064409;,
  0.343750;0.156250;,
  0.373591;0.248091;,
  0.451716;0.304853;,
  0.548284;0.304853;,
  0.626409;0.248091;,
  0.656250;0.156250;;
 }
}