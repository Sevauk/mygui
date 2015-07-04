#ifndef WIDGETS_HH_
# define WIDGETS_HH_

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <list>

class Widget {

  public:
    Widget(int, int, int, int, Widget *);
    void setWindow(sf::RenderWindow*);
    void setParent(Widget *);
    virtual sf::Vector2i draw();
    virtual sf::Vector2i getDimens() const;
    int getX() const { return mpx; }
    int getY() const { return mpy; }
    sf::Vector2i getPosRelative() const;
    void onEvent(sf::Event);
	int take(int idx, Widget *&);
	virtual const Widget *getFocused();
	virtual void setColor(const sf::Color& color);

    void setOnMouseDownListener(void (*ptr)(sf::Vector2i));
    virtual void OnMouseDown(sf::Vector2i pos);
    void setOnMouseUpListener(void (*ptr)(sf::Vector2i));
	virtual void OnMouseUp(sf::Vector2i);
    void setOnKeyPressedListener(void (*ptr)(sf::Keyboard::Key key));
	virtual void OnKeyPressed(sf::Keyboard::Key k);
    void setOnKeyReleasedListener(void (*ptr)(sf::Keyboard::Key key));
	virtual void OnKeyReleased(sf::Keyboard::Key);
    void setOnClickedListener(void (*ptr)(void));
	virtual void OnClicked();

  protected:
    int msx, msy, mpx, mpy;
    sf::RenderWindow *mwindow;
    Widget* parent;
    std::list<Widget *> children;
	sf::Color mColor;

    void (*mOnMouseDownListener)(sf::Vector2i pos) = NULL;
    void (*mOnMouseUpListener)(sf::Vector2i pos) = NULL;
    void (*mOnKeyPressedListener)(sf::Keyboard::Key) = NULL;
    void (*mOnKeyReleasedListener)(sf::Keyboard::Key) = NULL;
    void (*mOnClickedListener)(void) = NULL;

    void addWidget(Widget *);
	int take(int idx, int pos, Widget *&);
};

class Rectangle : public Widget {

  public:
    Rectangle(int, int, int, int, Widget *);
    virtual sf::Vector2i draw();

  protected:
    sf::RectangleShape rect;
};

class Label : public Widget {

  public:
    Label(int, int, const std::string& text, Widget *);
    virtual sf::Vector2i draw();
    void setText(const std::string&);
    void prepare();
    sf::Font font;

  protected:
    sf::Text text;
};

class Base : public Widget {

	public:
		Base(int, int, int, int, Widget *);
		void OnKeyPressed(sf::Keyboard::Key);
		void OnKeyReleased(sf::Keyboard::Key);
		const Widget *getFocused();

	private:
		unsigned focus_idx = 0;
		Widget *focused = NULL;

		bool hasShift = false;
		void focusNext();
};

class Point : public Rectangle {
	public:
		Point(int, int, Widget *);
};

class Button : public Rectangle {
	public:
		Button(int, int, const std::string&, Widget *);
		void OnMouseDown(sf::Vector2i);
		void OnMouseUp(sf::Vector2i);

	protected:
		Label text;
		bool isPressed = false;
};

class Line : public Rectangle {
	public:
		Line(int, int, int, int, Widget *);
};

class Picture : public Rectangle {
	public:
		Picture(int, int, int, int, const std::string&, Widget *);
		void setRepeated(bool);
		sf::Vector2i draw();

	private:
		sf::Texture texture;

};

#endif
