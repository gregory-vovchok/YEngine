// Win32.cpp: ���������� ����� ����� ��� ����������.
//


#include "Win32.h"
#include <Engine/Output/Graphics/Renderer/Renderer.h>

#include <Engine/Math/Angle/Angle.h>
#include <Engine/Math/Ratio/Ratio.h>
#include <Engine/Output/Graphics/Camera/Camera3D/Camera3D.h> 
#include <Engine/Output/Graphics/Font/Font2D/Font2D.h>
#include <Engine/Output/Graphics/GraphicsScene/GraphicsScene.h>
#include <Engine/Output/Graphics/Shape/Line/GraphicsLine/GraphicsLine.h>
#include <Engine/Output/Graphics/Shape/Point/GraphicsPoint/GraphicsPoint.h>
#include <Engine/Core/Time/Timer/AsyncTimer/AsyncTimer.h>
#include <Engine/Output/Graphics/Shape/Mesh/GraphicsMesh/GraphicsMesh.h>
#include <Engine/Core/Bitset/Bitset.h>
#include <Engine/Helpers/Scene/Scene.h>


// �����, ����������� ���������� �������������� �����������
class MyPixelImage: public PixelImage// ���������� �����������
{
	// METHODS
	// ������� ����������� ��������� ����� �������� _size
	public: void CreateCheckDeskImage(Size2D _size)
	{
		Resize(_size, RGBA());// ������� ���������� ����������� ������� �������
				
		// ��� ������� �������
		for(int32 i = 0; i < _size.height; i++) 
		{ 
			// ��� ������ ������
			for(int32 j = 0; j < _size.width; j++) 
			{ 
				/* ������ �������� ������ ����, ����� ������� */ 
				int32 c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255; // �������� ��� RGB ���������
				Pixel(Vector2D(j, i)) = RGBA((uint8)c,(uint8)c,(uint8)c,255);
			} 
		} 
	}
			
	// ������� ����������� �� ���������� ������� �������� _size
	public: void CreateRandomImage(Size2D _size)
	{
		Resize(_size, RGBA());// ������� ���������� ����������� ������� �������

		// ��� ������� �������
		for(int32 i = 0; i < _size.height; i++) 
		{ 
			// ��� ������ ������
			for(int32 j = 0; j < _size.width; j++) 
			{ 
				/* ������ �������� ������ ����, ����� ������� */ 
				Pixel(Vector2D(j, i)) = Color<RGBA>::_Random(5, 200);
			} 
		} 
	}
};



// �����, ����������� ���������� ����������� ���� (������� �������������)
class Quad2D: public GraphicsMesh<Vector3D, Quaternion, Matrix4x4>,// ���������� ����������� ������������� �����
	          public TexturedMaterial<Vector3D>// ���������������� ��������
{
	// METHODS
	// ����������� �� ���������
	public: Quad2D(void)
	{
		GraphicsMesh::Define def;
		Create(def);
	}


	// ���������� ������������� ����� �� ����� 
	public: virtual void Draw(void)
	{
		BeginTransform();
		GraphicsMesh::Draw();
		EndTransform();
	}

	

	// ���������� ����� ���������� ������� � ���� ������
	public: StringANSI FilteringModeString(void)const
	{
		if(GetTexture())
		{
			switch(GetTexture()->GetFilteringMode())
			{
				case Texture2D::POINT:
				{
					return "POINT";
				}
				case Texture2D::BILINEAR:
				{
					return "BILINEAR";
				}
				case Texture2D::TRILINEAR:
				{
					return "TRILINEAR";
				}
			}
		}
		return "NON";
	}
};


// �����, ����������� ���������������� ����
class Application: public Renderer
{
	// DATA
	private: Camera3D* camera;// ������
    private: Font2D* font2d;// �����
	private: Scene* scene;// ����������� �����
	private: Quad2D* quad1, *quad2;// ���������� ����������� ����
	private: Texture2D *texture;// ��������� �� ��������



    // METHODS
    // ���������������� �����������
	public: Application(void): camera(NIL), font2d(NIL), scene(NIL), quad1(NIL), quad2(NIL), texture(NIL)
	{}

			
	// ����������� ����������
	public: virtual ~Application(void)
	{
		delete scene;
	} 

	// ������� ����������
	public: bool Create(Renderer::Define _define)
	{
		// ������� ����������� ����
		if(Renderer::Create(_define))
		{
			// �����...
			{
				
				scene = new Scene();
			}


			// �����...
			{
				Font2D::_CheckSupportedFonts(this);// ������������� ������ �������������� �������

				Font2D::Define def;
				def.name = "font2d";
				def.fontName = "Haettenschweiler";
				def.fontSize = 20;
				def.textColor = RGBA(RGBA::WHITE_COLOR);

				font2d = new Font2D();
				font2d->Create(def);
				scene->AddObject(font2d);
				font2d->Pick();
			}


			// ��������...
			{
				texture = new Texture2D();
				//Texture2D::Define def;
				//def.name = "texture1";
				//def.sizeOfImage = Size2D(256, 256);
				texture->Create("image.png");
				texture->Rename("image");


				scene->AddObject(texture);// �������� � �����	
			}
			


						
			// ������������� �����...
			{
				// ������� ������������� �����, ����������� ����
				quad1 = new Quad2D();  
				quad1->CreateQuad2D(Quad<Vector3D>(Vector3D(),Size2D(1,1)));
				quad1->SetPosition(Vector3D(1,0,-1.5));// ���������� ���� ������ ������ �� ��� Z
				quad1->Rename("quad1");

				// ���������� ��������
				quad1->BindTexture(texture);// ��������� �������� texture � ������������� �����
				//quad1->ComputeTexelsForQuadShape();// ��������� ������� ��� �����
				quad1->SetEnable(true);// �������� ��������
		
				scene->AddObject(quad1);// �������� � �����	
				scene->AddGraphicsObject(quad1);
			}  
			
			// ������������� �����...
			{
				// ������� ������������� �����, ����������� ����
				quad2 = new Quad2D();  
				quad2->CreateQuad2D(Quad<Vector3D>(Vector3D(),Size2D(1,1)));
				quad2->SetPosition(Vector3D(-1,0,-2));// ���������� ���� ������ ������ �� ��� Z
				quad2->Rename("quad2");

				// ���������� ��������
				quad2->BindTexture(texture);// ��������� �������� texture � ������������� �����
				//quad2->ComputeTexelsForQuadShape();// ��������� ������� ��� �����
				quad2->SetEnable(true);// �������� ��������
	
				
				scene->AddObject(quad2);// �������� � �����	 
				scene->AddGraphicsObject(quad2);
			} 	
			
			
			 


			// ������...
			{
				Camera3D::Define def;
				def.name = "camera";
				def.rotationType = Camera3D::TRACKBALL_FIRST_PERSON; 
				def.movementType = Camera3D::OVERLAND;
				//def.viewingPoint = quad->GetPosition();
				def.zoomMin = 2;
				def.zoomMax = 10;


				camera = new Camera3D();
				camera->Create(def);
				scene->AddObject(camera);
				camera->Pick(Title()); 
				
				// ������ �������������� ������ ������
				//camera->UpdateTrackballObjectViewer(-Angle::HALF_PI/3.0f, Angle::HALF_PI/3.0f, 0.0f);
			}


			SetBackgroundColor(RGBA(RGBA::GRAY_COLOR));// ���� ����
			

			MoveToCenter();// ����������� ���� � ����� �����
			Mouse::_MoveCursorToCenter(this);// ����������� ������ � ����� ���������� ������� ����	
			Mouse::_ShowCursor(false);// ������ ������
			return true;// ������� �����
		}
		// ����� ������� �������
		return false;
	}




		


	// ������� �����
	public: virtual void Update(float _delta)
	{
		// ������� ����� �� �������� � �������
		//quad->SetPosition(quad->GetPosition() + Vector3D(0,0,0.01));
	}

	// ������� �������
	public: virtual void Draw(float _delta)
	{
		ClearScene();// �������� �����


		camera->BeginPerspective3D();// ������ ����� ���������� �������
		scene->Draw();
	
		// ����� ������...
		camera->BeginScreen2D();// ������ ����� ���������� �������

		int32 i = 0;
		
		
		font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "camera.position: %.2f/%.2f/%.2f", camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z); 

		//font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "IsBlendEnabled: %d", IsBlendEnabled()); 

		font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "AmountOfGraphicsObjects: %d", scene->AmountOfGraphicsObjects()); 

		

		if(quad1->GetTexture())
		{
			font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "quad1.texture.IsExist: %d", quad1->GetTexture()->IsExist()); 

			font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "quad1.texture.SizeOfImage: %.2f/%.2f", quad1->GetTexture()->ImageSize().width, quad1->GetTexture()->ImageSize().height); 
			font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "quad1.texture.SizeOfTexture: %.2f/%.2f", quad1->GetTexture()->TextureSize().width, quad1->GetTexture()->TextureSize().height); 
		}

	

		
	
		//int32 val;
		

		//uint64 uu = 0;
		//Bitset::_SetBit(uu, 0, 1);
		//font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "quad.texture.sizeOfTexture: %.2f/%.2f", quad->Texture()->SizeOfTexture().width, quad->Texture()->SizeOfTexture().height); 
		
		//font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "uu: %d", glGetTextureLevelParameteriv(GL_TEXTURE_2D, , 0, GL_TEXTURE_WIDTH)); 
		//Bitset::_SetBit(uu, 1, 1);
		//font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "uu: %s", Bitset::_String(uu).c_str()); 
		//font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "uu: %d", uu); 

		//font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "vertices: %d", mesh->AmountOfVertices()); 
		//font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "indices: %d", mesh->AmountOfIndices()); 
		//font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "normals: %d", mesh->AmountOfNormals()); 

		//font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "sizeinByte: %d", mesh->SizeInByte()); 
		//font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "sizeInKbyte: %.5f", MemoryCounter::_FromByteToKB(mesh->SizeInByte())); 
 


		/*
		font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "shape detail: %d", mesh->DetailLevel()); 
	    font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "shape name: %s", mesh->ShapeNameString().c_str()); 


		font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "colored material.type: %s", mesh->ColoredMaterialTypeString().c_str());

		font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "camera position: %.2f/%.2f/%.2f", camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z); 


		font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "shape attributes: %s", mesh->StringAttributes().c_str()); 
		font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "shape vertices: %d", mesh->AmountOfVertices()); 
		font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "shape polygons: %d", mesh->AmountOfPolygons()); 
		font2d->DrawScreenText(Vector3D(10, ClientAreaSize().height - (i+=20), -1), "shape vertex colors: %d", mesh->AmountOfVertexColors()); 

		*/ 


		// ��������������� �����...
		//camera->End2D();// ������ ����� ���������� �������
	}


	// ������ ������� ����
	public: virtual bool MouseEventFilter(Mouse::Event _event)
	{
		Mouse().ClearEventList();// �������� ����� �������
		return true;
	}


	// ��������� ������� ����������
	public: virtual bool KeyboardEventFilter(Keyboard::Event _event)
	{
		if(_event.type == Keyboard::KEY_DOWN)
		{
			if(_event.key == Keyboard::F1)
			{
				SetWindowStyle(Window::FULLSCREEN);
			}
			else if(_event.key == Keyboard::F2)
			{
				SetWindowStyle(Window::WND_CLASSIC);
			}
			else if(_event.key == Keyboard::ESC)
			{
				Destroy();// ���������� ����
			} 
			else if(_event.key == Keyboard::RIGHT_ARROW)
			{
				quad1->SetPosition(quad1->GetPosition() + Vector3D(0.1, 0, 0));
			}
			else if(_event.key == Keyboard::LEFT_ARROW)
			{
				quad1->SetPosition(quad1->GetPosition() + Vector3D(-0.1, 0, 0));
			}
			else if(_event.key == Keyboard::UP_ARROW)
			{
				quad1->SetPosition(quad1->GetPosition() + Vector3D(0, 0.1, 0));
			}
			else if(_event.key == Keyboard::DOWN_ARROW)
			{
				quad1->SetPosition(quad1->GetPosition() + Vector3D(0, -0.1, 0));
			}
			else if(_event.key == Keyboard::P)
			{
				// ������� ��������, � ������� � ��� ����������� ���������� ������� ����
				Texture2D txr;
				txr.Create(ClientAreaSize());
				txr.FromScreen(Vector2D(), ClientAreaSize());

				// ���������� ����������� � .png ����
				PixelImage image;
				txr.GetImage(image);
				image.SaveImageToPNGFile("screenshot.png");
			}
		}

		Keyboard().ClearEventList();// �������� ����� �������
		return true;
	}
};



// ������� ����� ����� � ���������
// ���������� � ������ ������� WINAPI, ���������, ��� ��������� � ������� WinMain ���������� ����� �������
int WINAPI WinMain(HINSTANCE hInstance,// ���������� (�������������), ������������ �������� ��� ������� ����������
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
	// �������� ������������ ����
	Renderer::Define def;
	def.realTimeWorkerDef.windowDef.SetTemplateStyle(Window::WND_RESIZING);// ����� ���� 
	def.realTimeWorkerDef.windowDef.clientAreaSize.Set(800, 600);
	def.realTimeWorkerDef.windowDef.hSmallIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL)); // ��������� ������ small.ico �� ��������
	def.realTimeWorkerDef.windowDef.tittle = "Texture2D.example_03";
	//def.realTimeWorkerDef.unsuspended = false;
	//def.realTimeWorkerDef.sleep = false;
	//def.faceDrawMode[Renderer::FRONT] = Renderer::LINE;
	//def.faceDrawMode[Renderer::BACK] = Renderer::LINE;
	//def.faceCullMode[Renderer::FRONT] = false;
	
	//def.faceCullMode[Renderer::BACK] = false;
	def.zBufferEnabled = false;
	//def.blendEnable = true;// �������� ����������
	
	//def.frontFaceClockwise = true;
	//def.realTimeWorkerDef.windowDef.eventBuffering = true;
	//def.vSync = false;
	//def.drawCallController.SetMode(CallController::UNLIM);

	
	Application* app = new Application;// ������� ����
	
	if(app->Application::Create(def))
	{
		app->Loop();// ��������� ���� �������
	}
	delete app;
	return 0;
}
