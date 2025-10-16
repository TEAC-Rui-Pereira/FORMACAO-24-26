# Light Intensity Management Web Application

This project is a web application designed to manage light intensity using a frontend built with React and a backend powered by Node.js and Express. The application allows users to monitor and control light intensity in real-time.

## Project Structure

The project is divided into two main parts: the frontend and the backend.

### Frontend

- **public/index.html**: The main HTML file that serves as the entry point for the web application.
- **src/App.tsx**: The main component of the React application, setting up routing and layout.
- **src/index.tsx**: The entry point for the React application, rendering the App component.
- **src/components/Dashboard.tsx**: Displays the current light intensity and relevant information.
- **src/components/LightControl.tsx**: Allows users to control the light intensity with sliders or buttons.
- **src/hooks/useSensor.ts**: Custom hook for managing sensor data and fetching light intensity from the backend.
- **src/services/api.ts**: Functions for making API calls to the backend for fetching and updating light intensity.
- **src/styles/main.css**: CSS styles for the application, defining layout and appearance.
- **src/types/index.d.ts**: TypeScript types and interfaces used throughout the frontend.

### Backend

- **src/index.ts**: Entry point for the backend application, setting up the Express server and middleware.
- **src/controllers/lightController.ts**: Handles requests related to light intensity, including fetching and updating values.
- **src/routes/lightRoutes.ts**: Defines the API routes for light intensity and links them to the controller.
- **src/services/lightService.ts**: Contains business logic for managing light intensity and interacting with data sources.
- **src/types/index.ts**: TypeScript types and interfaces used throughout the backend.

## Setup Instructions

1. **Clone the repository**:
   ```
   git clone <repository-url>
   cd light-intensity-web
   ```

2. **Install dependencies**:
   - For the frontend:
     ```
     cd frontend
     npm install
     ```
   - For the backend:
     ```
     cd backend
     npm install
     ```

3. **Configure environment variables**:
   - Copy `.env.example` to `.env` in the backend directory and set the necessary environment variables.

4. **Run the application**:
   - Start the backend server:
     ```
     cd backend
     npm start
     ```
   - Start the frontend application:
     ```
     cd frontend
     npm start
     ```

## Usage

- Access the web application in your browser at `http://localhost:3000`.
- Use the dashboard to view current light intensity and control it using the provided controls.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any enhancements or bug fixes.

## License

This project is licensed under the MIT License.