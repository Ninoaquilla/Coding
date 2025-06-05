const sidebar = document.getElementById('sidebar');
const menuButton = document.getElementById('menu-button');

menuButton.addEventListener('click', () => {
    const isOpen = menuButton.getAttribute('aria-expanded') === 'true';
    menuButton.setAttribute('aria-expanded', !isOpen);
    sidebar.classList.toggle('active');
});

document.addEventListener('keydown', (e) => {
    if (e.key === 'Escape' && sidebar.classList.contains('active')) {
        sidebar.classList.remove('active');
        menuButton.setAttribute('aria-expanded', 'false');
    }
});