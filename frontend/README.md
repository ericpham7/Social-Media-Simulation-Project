# EricGram Frontend - Social Media Simulation

This is the frontend for the **EricGram** social media simulation project, built with **React**, **Vite**, and **React Router**. It communicates with a **C++ backend** to handle user authentication and data.

## 🚀 Recent Changes & Features

### 1. Multi-Tab Navigation

- The "Log in" button on the home page now opens the login screen in a **new browser tab**.
- This was implemented using the `window.open('/login', '_blank')` browser API.

### 2. Client-Side Routing

- Added **React Router** (`react-router-dom`) to manage navigation within the application.
- **Routes Defined**:
  - `/`: The Home page with the welcome message and login button.
  - `/login`: The standalone Login page.

### 3. Backend Integration

- The `LoginPage` component is configured to send `POST` requests to the C++ backend.
- **Endpoint**: `http://localhost:8080/api/login` (configurable to `https` if your server uses SSL).
- **Functionality**: Extracts email and password from the form, sends them as JSON, and handles success/error responses.

### 4. UI Fixes

- Fixed the CSS class selector for `.log-in-button` in `App.css` to ensure styles are applied correctly.
- Reformatted `loginPage.jsx` for better code readability and maintainability.

## 🛠️ How to Run

1. **Install Dependencies** (if you haven't already):

   ```bash
   cd frontend
   npm install
   ```

2. **Start the Development Server**:

   ```bash
   npm run dev
   ```

3. **Backend Connection**:
   Ensure your C++ backend is compiled and running on `localhost:8080`.

## 📂 Project Structure

- `src/App.jsx`: Main application controller and route definitions.
- `src/components/loginPage.jsx`: The login form component with backend logic.
- `src/App.css`: Styles for the home page and login button.
- `src/main.jsx`: Application entry point.

---

_Developed as part of the Social Media Simulation Project._
