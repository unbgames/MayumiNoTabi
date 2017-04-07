#include <tileMap.hpp>
#include <tileSet.hpp>

TileMap::TileMap(string file,TileSet* ts){
	Load(file);
	SetTileSet(ts);
}


void TileMap::Load(string file){
	int x;
	string line;
	std::ifstream in;
	in.open(file);
	if(!in.is_open()){
		cout << "Erro ao abrir o arquivo \"" << file << "\", o programa ira encerrar agora" << endl;
		exit(EXIT_FAILURE);
	}
	getline(in,line);
	sscanf(line.c_str()," %d,%d,%d,",&mapWidth,&mapHeight,&mapDepth);

	tileMatrix.reserve(mapWidth*mapHeight*mapDepth);
	tileMatrixMeta.reserve(mapWidth*mapHeight);

	FOR(d,mapDepth){
		FOR(h,mapHeight){
			FOR(w,mapWidth){
				in >> x;
				in.ignore(1);
				At(w,h,d) = x-1;
			}
		}
	}
	FOR(h,mapHeight){
		FOR(w,mapWidth){
			in >> x;
			in.ignore(1);
			AtMeta(w,h) = x;
		}
	}
	in.close();
}

void TileMap::SetTileSet(TileSet* ts){
	tileSet = ts;
}

int& TileMap::At(int x,int y,int z){
	return tileMatrix[x+(y*mapWidth)+(z*(mapWidth*mapHeight))];
}

const int& TileMap::At(int x,int y,int z) const{
	return tileMatrix[x+(y*mapWidth)+(z*(mapWidth*mapHeight))];
}

int& TileMap::AtMeta(int x,int y){
	return tileMatrixMeta[x+(y*mapWidth)];
}

const int& TileMap::AtMeta(int x,int y) const{
	return tileMatrixMeta[x+(y*mapWidth)];
}

void TileMap::Render(int cameraX,int cameraY) const{
	FOR(i,mapDepth){
		RenderLayer(i,cameraX,cameraY);
	}
}

void TileMap::RenderLayer(int layer,int cameraX,int cameraY) const{
	int w=tileSet->GetWidth();
	int h=tileSet->GetHeight();
	FOR(y,mapHeight){
		FOR(x,mapWidth){
			tileSet->Render(At(x,y,layer),(x*w)-cameraX,(y*h)-cameraY);
		}
	}
}

int TileMap::GetWidth() const{
	return mapWidth;
}
int TileMap::GetHeight() const{
	return mapHeight;
}
int TileMap::GetDepth() const{
	return mapDepth;
}

void TileMap::GetIndAtPos(const int x,const int y,int &outX,int &outY) const{
	int tileW=tileSet->GetWidth(),tileH=tileSet->GetHeight();
	FOR(j,mapHeight){
		FOR(i,mapWidth){
			if(BETWEEN(x,i*tileW,(i+1)*tileW) && BETWEEN(y,j*tileH,(j+1)*tileH)){
				outX=i;
				outY=j;
				return;
			}
		}
	}
}
