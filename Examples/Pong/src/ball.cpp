#include "ball.hpp"
#include "consts.hpp"

Ball::Ball(ShapeRenderer& renderer): renderer(renderer) {
    this->position = glm::vec2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 2.0f * M_PI);

    float angle = dist(gen);
    this->velocity = glm::vec2(std::cos(angle), std::sin(angle)) * BALL_SPEED;
}

glm::vec2 Ball::getPosition() {
    return this->position;
}

void Ball::draw() {
    this->renderer.DrawCircle(
        this->position,
        glm::vec2(1.0f, 1.0f),
        BALL_SIZE,
        BALL_COLOR
    );
}

void Ball::update() {
    this->position += this->velocity;

    // Vertical bounce
    if (this->position.y <= 0 || this->position.y >= SCREEN_HEIGHT)
        this->velocity.y *= -1;

    // Check if opponent scored
    if (this->position.x <= 0) {
        // TODO inform game manager
        this->position = glm::vec2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
        this->velocity.x *= -1;
        std::cout << "Computer wins" << std::endl;
    }

    // Check if player scored
    if (this->position.x >= SCREEN_WIDTH) {
        // TODO inform game manager
        this->position = glm::vec2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
        this->velocity.x *= -1;
        std::cout << "Player wins" << std::endl;
    }
}

void Ball::checkBouncePaddle(double paddle_pos, bool is_player) {
    /**
     * This part is super weird until you realize two things
     * Firstly: (0,0) is the top left of the screen
     * Secondly: The paddle position is actually its center
     *
     * To explain how we calculate this we will need to use out **imagination**
     * Imagine that the paddle top is at height 0 (the top of the screen),
     * now we know that it's bottom is at PADDLE_HEIGHT.
     *
     * We can calculate the remapped ball position by just adding the original paddle top
     */

    // check if ball is in the right area
    bool in_zone;
    if (is_player) in_zone = this->position.x <= PADDLE_OFFSET && this->position.x > PADDLE_OFFSET - PADDLE_WIDTH;
    else in_zone = this->position.x >= SCREEN_WIDTH - PADDLE_WIDTH - PADDLE_OFFSET && this->position.x < SCREEN_WIDTH - PADDLE_OFFSET;
    if (!in_zone) return;

    std::cout << "Ball in paddle zone" << std::endl;

    // TODO fix is_touching (collision detection is off)
    bool is_touching = this->position.y < paddle_pos && this->position.y > paddle_pos - PADDLE_HEIGHT;
    if (!is_touching) return;

    std::cout << "Ball should bounce from paddle" << std::endl;

    // TODO switch to having player be drawn from corner
    // Its way more intuitive that way. Preferably top left corner
    double ball_remapped = this->position.y - paddle_pos + PADDLE_HEIGHT;
    double paddle_range = ball_remapped / PADDLE_HEIGHT;
    double ball_angle = (M_PI * paddle_range) - M_PI / 2.0;

    // Update ball direction
    this->velocity = glm::vec2(std::cos(ball_angle), std::sin(ball_angle)) * BALL_SPEED;

    // Flip direction for computer
    if (!is_player)
        this->velocity *= -1;
}
