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
 47;
 -0.80627;0.45470;0.32044;,
 -1.49529;-0.62684;0.32044;,
 -0.64800;-1.72317;0.51816;,
 0.54541;0.15012;0.51816;,
 -1.83980;-1.16761;0.05035;,
 -1.24471;-2.65981;0.05035;,
 -1.49529;-0.62684;-0.21974;,
 -0.64800;-1.72317;-0.41746;,
 -0.80627;0.45470;-0.21974;,
 0.54541;0.15012;-0.41746;,
 -0.46176;0.99547;0.05035;,
 1.14212;1.08677;0.05035;,
 -0.80627;0.45470;0.32044;,
 0.54541;0.15012;0.51816;,
 0.76161;-2.82490;0.59053;,
 2.13965;-0.66181;0.59053;,
 0.07259;-3.90644;0.05035;,
 0.76161;-2.82490;-0.48984;,
 2.13965;-0.66181;-0.48984;,
 2.82867;0.41973;0.05035;,
 2.13965;-0.66181;0.59053;,
 2.35585;-3.63683;0.51816;,
 3.54927;-1.76354;0.51816;,
 1.75914;-4.57348;0.05035;,
 2.35585;-3.63683;-0.41746;,
 3.54927;-1.76354;-0.41746;,
 4.14598;-0.82690;0.05035;,
 3.54927;-1.76354;0.51816;,
 3.70754;-3.94141;0.32044;,
 4.39656;-2.85987;0.32044;,
 3.36303;-4.48218;0.05035;,
 3.70754;-3.94141;-0.21974;,
 4.39656;-2.85987;-0.21974;,
 4.74107;-2.31910;0.05035;,
 4.39656;-2.85987;0.32044;,
 -1.55322;0.17031;0.05035;,
 -1.55322;0.17031;0.05035;,
 -1.55322;0.17031;0.05035;,
 -1.55322;0.17031;0.05035;,
 -1.55322;0.17031;0.05035;,
 -1.55322;0.17031;0.05035;,
 4.45449;-3.65702;0.05035;,
 4.45449;-3.65702;0.05035;,
 4.45449;-3.65702;0.05035;,
 4.45449;-3.65702;0.05035;,
 4.45449;-3.65702;0.05035;,
 4.45449;-3.65702;0.05035;;
 
 36;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;3,2,14,15;,
 4;2,5,16,14;,
 4;5,7,17,16;,
 4;7,9,18,17;,
 4;9,11,19,18;,
 4;11,13,20,19;,
 4;15,14,21,22;,
 4;14,16,23,21;,
 4;16,17,24,23;,
 4;17,18,25,24;,
 4;18,19,26,25;,
 4;19,20,27,26;,
 4;22,21,28,29;,
 4;21,23,30,28;,
 4;23,24,31,30;,
 4;24,25,32,31;,
 4;25,26,33,32;,
 4;26,27,34,33;,
 3;1,0,35;,
 3;4,1,36;,
 3;6,4,37;,
 3;8,6,38;,
 3;10,8,39;,
 3;12,10,40;,
 3;29,28,41;,
 3;28,30,42;,
 3;30,31,43;,
 3;31,32,44;,
 3;32,33,45;,
 3;33,34,46;;
 
 MeshMaterialList {
  14;
  36;
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.064000;0.024000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.648000;0.448000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.648000;0.448000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.648000;0.448000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.648000;0.448000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.648000;0.448000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.648000;0.448000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.648000;0.448000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.648000;0.448000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.392000;0.216000;0.112000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.064000;0.024000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.064000;0.264000;0.064000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.192000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  44;
  -0.270858;0.372375;0.887678;,
  -0.451955;0.088109;0.887679;,
  -0.612259;-0.004836;0.790643;,
  -0.451955;0.088109;-0.887679;,
  -0.270858;0.372375;-0.887678;,
  -0.254369;0.556940;-0.790642;,
  -0.010724;0.237790;0.971257;,
  -0.220044;-0.090775;0.971257;,
  -0.351183;-0.229632;0.907711;,
  -0.220046;-0.090775;-0.971257;,
  -0.010726;0.237792;-0.971257;,
  0.059700;0.415327;-0.907711;,
  0.106291;0.166845;0.980237;,
  -0.106292;-0.166844;0.980237;,
  -0.208580;-0.327404;0.921575;,
  -0.106293;-0.166846;-0.980237;,
  0.106292;0.166846;-0.980237;,
  0.208581;0.327407;-0.921574;,
  0.220043;0.090775;0.971257;,
  0.010724;-0.237790;0.971257;,
  -0.059701;-0.415325;0.907712;,
  0.010726;-0.237792;-0.971257;,
  0.220046;0.090775;-0.971257;,
  0.351184;0.229632;-0.907711;,
  0.451955;-0.088109;0.887679;,
  0.270858;-0.372375;0.887678;,
  0.254369;-0.556940;0.790642;,
  0.270858;-0.372375;-0.887678;,
  0.451955;-0.088109;-0.887679;,
  0.612259;0.004836;-0.790642;,
  -0.565056;0.359982;0.742378;,
  0.565056;-0.359982;0.742377;,
  -0.612259;-0.004836;-0.790643;,
  -0.351185;-0.229632;-0.907711;,
  -0.254369;0.556940;0.790642;,
  0.059701;0.415325;0.907712;,
  -0.208581;-0.327407;-0.921574;,
  0.208579;0.327404;0.921575;,
  -0.059700;-0.415327;-0.907711;,
  0.351182;0.229632;0.907712;,
  0.254369;-0.556940;-0.790642;,
  0.612259;0.004836;0.790642;,
  -0.565056;0.359982;-0.742378;,
  0.565056;-0.359982;-0.742377;;
  36;
  4;0,1,7,6;,
  4;1,2,8,7;,
  4;32,3,9,33;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;34,0,6,35;,
  4;6,7,13,12;,
  4;7,8,14,13;,
  4;33,9,15,36;,
  4;9,10,16,15;,
  4;10,11,17,16;,
  4;35,6,12,37;,
  4;12,13,19,18;,
  4;13,14,20,19;,
  4;36,15,21,38;,
  4;15,16,22,21;,
  4;16,17,23,22;,
  4;37,12,18,39;,
  4;18,19,25,24;,
  4;19,20,26,25;,
  4;38,21,27,40;,
  4;21,22,28,27;,
  4;22,23,29,28;,
  4;39,18,24,41;,
  3;1,0,30;,
  3;2,1,30;,
  3;3,32,42;,
  3;4,3,42;,
  3;5,4,42;,
  3;0,34,30;,
  3;24,25,31;,
  3;25,26,31;,
  3;40,27,43;,
  3;27,28,43;,
  3;28,29,43;,
  3;41,24,31;;
 }
 MeshTextureCoords {
  47;
  0.000000;0.833333;,
  0.166667;0.833333;,
  0.166667;0.666667;,
  0.000000;0.666667;,
  0.333333;0.833333;,
  0.333333;0.666667;,
  0.500000;0.833333;,
  0.500000;0.666667;,
  0.666667;0.833333;,
  0.666667;0.666667;,
  0.833333;0.833333;,
  0.833333;0.666667;,
  1.000000;0.833333;,
  1.000000;0.666667;,
  0.166667;0.500000;,
  0.000000;0.500000;,
  0.333333;0.500000;,
  0.500000;0.500000;,
  0.666667;0.500000;,
  0.833333;0.500000;,
  1.000000;0.500000;,
  0.166667;0.333333;,
  0.000000;0.333333;,
  0.333333;0.333333;,
  0.500000;0.333333;,
  0.666667;0.333333;,
  0.833333;0.333333;,
  1.000000;0.333333;,
  0.166667;0.166667;,
  0.000000;0.166667;,
  0.333333;0.166667;,
  0.500000;0.166667;,
  0.666667;0.166667;,
  0.833333;0.166667;,
  1.000000;0.166667;,
  0.083333;1.000000;,
  0.250000;1.000000;,
  0.416667;1.000000;,
  0.583333;1.000000;,
  0.750000;1.000000;,
  0.916667;1.000000;,
  0.083333;0.000000;,
  0.250000;0.000000;,
  0.416667;0.000000;,
  0.583333;0.000000;,
  0.750000;0.000000;,
  0.916667;0.000000;;
 }
}
