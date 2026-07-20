use crossterm::event;

fn main() -> std::io::Result<()> {
    ratatui::run(|mut terminal| {
        loop {
            terminal.draw(|frame| frame.render_widget("Hello world", frame.area()))?;
            if event::read()?.is_key_press() {
                break Ok(());
            }
        }
    })
}
