import pygame
import sys
import random

# Initialize Pygame
pygame.init()

# ----------------------
# GAME SETTINGS
# ----------------------
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
FPS = 60

SHIP_SPEED = 5
BULLET_SPEED = 10
ALIEN_SPEED = 2
ALIEN_DROP_INTERVAL = 30  # Frames between dropping a new row of aliens

# Colors (R, G, B)
WHITE = (255, 255, 255)
BLACK = (0,   0,   0)
GREEN = (0, 255,   0)
RED   = (255,   0, 0)

# Set up the display
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Alien Invasion (Simplified)")

clock = pygame.time.Clock()

# ----------------------
# GAME OBJECTS
# ----------------------
class Ship(pygame.sprite.Sprite):
    """Player-controlled ship that can move and shoot bullets."""
    def __init__(self):
        super().__init__()
        self.image = pygame.Surface((50, 30))
        self.image.fill(GREEN)
        self.rect = self.image.get_rect()
        self.rect.midbottom = (SCREEN_WIDTH // 2, SCREEN_HEIGHT - 20)
        self.speed = SHIP_SPEED

    def update(self, keys_pressed):
        """Move the ship based on key presses."""
        if keys_pressed[pygame.K_LEFT] and self.rect.left > 0:
            self.rect.x -= self.speed
        if keys_pressed[pygame.K_RIGHT] and self.rect.right < SCREEN_WIDTH:
            self.rect.x += self.speed

    def shoot(self, bullet_group, all_sprites_group):
        """Create a new bullet and add it to the relevant sprite groups."""
        bullet = Bullet(self.rect.centerx, self.rect.top)
        bullet_group.add(bullet)
        all_sprites_group.add(bullet)


class Bullet(pygame.sprite.Sprite):
    """Bullet fired by the player's ship."""
    def __init__(self, x, y):
        super().__init__()
        self.image = pygame.Surface((5, 10))
        self.image.fill(WHITE)
        self.rect = self.image.get_rect()
        self.rect.centerx = x
        self.rect.bottom = y
        self.speed = BULLET_SPEED

    def update(self, *args):
        """Move the bullet upwards; kill it if it goes off-screen."""
        self.rect.y -= self.speed
        if self.rect.bottom < 0:
            self.kill()


class Alien(pygame.sprite.Sprite):
    """Single alien sprite that moves downward."""
    def __init__(self, x, y):
        super().__init__()
        self.image = pygame.Surface((40, 30))
        self.image.fill(RED)
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y
        self.speed = ALIEN_SPEED

    def update(self, *args):
        """Move the alien downward; kill it if it goes off-screen."""
        self.rect.y += self.speed
        if self.rect.top > SCREEN_HEIGHT:
            self.kill()

# ----------------------
# MAIN GAME FUNCTION
# ----------------------
def run_game():
    # Sprite groups
    all_sprites = pygame.sprite.Group()
    bullet_group = pygame.sprite.Group()
    alien_group = pygame.sprite.Group()

    # Create player ship
    ship = Ship()
    all_sprites.add(ship)

    # Game loop variables
    running = True
    alien_timer = 0  # For controlling alien drops

    while running:
        clock.tick(FPS)
        keys_pressed = pygame.key.get_pressed()

        # Process input events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    ship.shoot(bullet_group, all_sprites)

        # Update logic
        ship.update(keys_pressed)
        bullet_group.update()
        alien_group.update()

        # Collision detection: check if bullets hit aliens
        collisions = pygame.sprite.groupcollide(bullet_group, alien_group, True, True)

        # Possibly spawn new aliens every ALIEN_DROP_INTERVAL frames
        alien_timer += 1
        if alien_timer % ALIEN_DROP_INTERVAL == 0:
            # Create a row of aliens
            for i in range(0, SCREEN_WIDTH, 80):
                alien = Alien(i, 0)
                alien_group.add(alien)
                all_sprites.add(alien)

        # Drawing
        screen.fill(BLACK)
        all_sprites.draw(screen)
        pygame.display.flip()

    pygame.quit()
    sys.exit()

# ----------------------
# ENTRY POINT
# ----------------------
if __name__ == "__main__":
    run_game()
