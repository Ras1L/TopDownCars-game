#include "menu_state.hpp"

MenuState::MenuState(StateStack& stack, Context context)
: mGUIContainer()
{
    // logic of "Play"
    sf::Text playOption;
    playOption.setFont(sf::Font());
    playOption.setString("Play");
    // centerOrigin(playOption);
    playOption.setPosition(context.window->getView().getSize() / 2.f);
    mOptions.push_back(playOption);

    // interface of "Play"
    auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    playButton->setPosition(100, 250);
    playButton->setText("Play");
    playButton->setCallBack
    (
        [this]()
        {
            requestStackPop();
            requestStackPush(States::Game);
        }
    );
    mGUIContainer.pack(playButton);
}

void MenuState::updateOptionText() // invokes every time as mOptionIndex changes
{
    if (!mOptions.empty()){
        return;
    }

    // White all text
    std::for_each(mOptions.begin(), mOptions.end(),
    [](sf::Text& text) -> void
    {
        text.setColor(sf::Color::White);
    });

    // Red the selected option
    mOptions[mOptionIndex].setColor(sf::Color::Red);
}


void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    // window.draw(mBackGroundSprite);
    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time deltaTime)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    mGUIContainer.handleEvent(event);
    return false;

    // if (event.key.code == sf::Keyboard::Up)
    // {
    //     if (mOptionIndex > 0){
    //         --mOptionIndex;
    //     }
    //     else {
    //         mOptionIndex = mOptions.size() - 1;
    //     }
    //     updateOptionText();
    // }
    // if (event.key.code == sf::Keyboard::Down)
    // {
    //     if (mOptionIndex < mOptions.size() - 1){
    //         ++mOptionIndex;
    //     }
    //     else {
    //         mOptionIndex = 0;
    //     }
    //     updateOptionText();
    // }
    // if (event.key.code == sf::Keyboard::Return)
    // {
    //     if (mOptionIndex == Play)
    //     {
    //         requestStackPop();
    //         requestStackPush(States::Game);
    //     }
    //     else if (mOptionIndex == Exit)
    //     {
    //         requestStackPop(); // requestStackClear() is concern of Application class
    //     }
    // }
}