#include "myToolScene.h"
#include "myApplication.h"
#include "myImage.h"
#include "myResourceManager.h"
#include "TileMap_Tool.h"
#include "myObject.h"
#include "myInput.h"
#include "Resource.h"

extern my::Application myapplication;

namespace my
{

    ToolScene::ToolScene()
    {
    }

    ToolScene::~ToolScene()
    {
    }

    void ToolScene::Initialize()
    {
        Scene::Initialize();

        my::Image* tile = my::ResourceManager::Find<my::Image>(L"TileAtlas");

        TileMap_Tool* test = object::Instantiate<TileMap_Tool>(eLayerType::UI);
        test->InitializeTile(tile, 0);



        //test = object::Instantiate<Tile>(eLayerType::Tile);
        //test->InitializeTile(tile, 1);
    }

    void ToolScene::Update()
    {
        Scene::Update();

        Vector2  temp = Input::GetMousePos();
    }

    void ToolScene::Render(HDC hdc)
    {


        HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
        HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

        int maxRow = myapplication.GetHeight() / TILE_SIZE_Y + 1;
        for (size_t y = 0; y < maxRow; y++)
        {
            MoveToEx(hdc, 0, TILE_SIZE_Y * y, NULL);
            LineTo(hdc, myapplication.GetWidth(), TILE_SIZE_Y * y);
        }
        int maxColumn = myapplication.GetWidth() / TILE_SIZE_X + 1;
        for (size_t x = 0; x < maxColumn; x++)
        {
            MoveToEx(hdc, TILE_SIZE_X * x, 0, NULL);
            LineTo(hdc, TILE_SIZE_X * x, myapplication.GetHeight());
        }
        (HPEN)SelectObject(hdc, oldPen);
        DeleteObject(redPen);


        Scene::Render(hdc);
    }

    void ToolScene::Release()
    {
        Scene::Release();
    }

    void ToolScene::OnEnter()
    {
    }

    void ToolScene::OnExit()
    {
    }
}

LRESULT CALLBACK AtlasWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        //512 384
        //HMENU mMenubar = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_CLIENT));
        //SetMenu(hWnd, mMenubar);
        my::Image* tile = my::ResourceManager::Load<my::Image>(L"TileAtlas", L"..\\Resources\\Tile.bmp");
        RECT rect = { 0, 0, tile->GetWidth(), tile->GetHeight() };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

        // 윈도우 크기 변경및 출력 설정
        SetWindowPos(hWnd
            , nullptr, 0, 0
            , rect.right - rect.left
            , rect.bottom - rect.top
            , 0);
        ShowWindow(hWnd, true);
    }

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
            //case IDM_ABOUT:
            //    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            //    break;
            //case IDM_EXIT:
            //    DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        my::Image* tile = my::ResourceManager::Find<my::Image>(L"TileAtlas");
        BitBlt(hdc, 0, 0, tile->GetWidth(), tile->GetHeight(), tile->GetHdc(), 0, 0, SRCCOPY);

        //HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        //HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

        //Ellipse(hdc, 0, 0, 100, 100);
        ////RoundRect(hdc, 200, 200, 300, 300, 500, 500);
        //(HPEN)SelectObject(hdc, oldPen);
        //DeleteObject(redPen);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}