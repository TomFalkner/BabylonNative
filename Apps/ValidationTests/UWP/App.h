#pragma once

// NOMINMAX to prevent compilation errors with bgfx
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#include <Babylon/AppRuntime.h>
#include <Babylon/Graphics/Device.h>
#include <Babylon/Polyfills/Canvas.h>

// Main entry point for our app. Connects the app with the Windows shell and handles application lifecycle events.
ref class App sealed : public Windows::ApplicationModel::Core::IFrameworkView
{
public:
    App();

    // IFrameworkView Methods.
    virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
    virtual void SetWindow(Windows::UI::Core::CoreWindow^ window);
    virtual void Load(Platform::String^ entryPoint);
    virtual void Run();
    virtual void Uninitialize();

private:
    // Application lifecycle event handlers.
    void OnActivated(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView, Windows::ApplicationModel::Activation::IActivatedEventArgs^ args);
    void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
    void OnResuming(Platform::Object^ sender, Platform::Object^ args);

    // Window event handlers.
    void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args);
    void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args);

    // DisplayInformation event handlers.
    void OnDpiChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);

    void RestartRuntime(Windows::Foundation::Rect bounds);

    std::optional<Babylon::Graphics::Device> m_device{};
    std::optional<Babylon::Graphics::DeviceUpdate> m_update{};
    std::optional<Babylon::AppRuntime> m_runtime{};
    std::optional<Babylon::Polyfills::Canvas> m_nativeCanvas{};

    Windows::Foundation::Collections::IVectorView<Windows::Storage::IStorageItem^>^ m_files;
    bool m_windowClosed;
    bool m_windowVisible;
    float m_displayScale{ 1.f };
};

ref class Direct3DApplicationSource sealed : Windows::ApplicationModel::Core::IFrameworkViewSource
{
public:
    virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView();
};
