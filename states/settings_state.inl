#include "settings_state.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
    mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

    mBindingButtons[Player::MoveLeft] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    mBindingLabels[Player::MoveLeft]  = std::make_shared<GUI::Label>("MoveLeft", *context.fonts);
    // More buttons and labels
    updateLabels();
    auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    backButton->setPosition(100, 375);
    backButton->setText("Back");
    backButton->setCallBack([this] ()
    {
        requestStackPop();
    });

    mGUIContainer.pack(mBindingButtons[Player::MoveLeft]);
    mGUIContainer.pack(mBindingLabels[Player::MoveLeft]);
    mGUIContainer.pack(backButton);
}

void SettingsState::updateLabels()
{
    Player& player = *getContext().player;

    for (std::size_t i = 0; i < Player::ActionCount; ++i)
    {
        sf::Keyboard::Key key = player.getAssignKey(static_cast<Player::Action>(i));
        mBindingLabels[i]->setText(std::to_string(key));
    }
}


bool SettingsState::handleEvent(const sf::Event& event)
{
    bool isKeyBinding = false;

    for (std::size_t action = 0; action != Player::ActionCount; ++action)
    {
        if (mBindingButtons[action]->isActive())
        {
            isKeyBinding = true;
            if (event.type == sf::Event::KeyReleased)
            {
                getContext().player->assignKey
                (
                    static_cast<Player::Action>(action), event.key.code
                );
                mBindingButtons[action]->deactivate();
            }
            break;
        }
    }
    if (isKeyBinding){
        updateLabels();
    }
    else {
        mGUIContainer.handleEvent(event);
    }
    return false;
}