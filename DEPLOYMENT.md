# SustainHub WebApp - Deployment Guide

## Development Mode (Separate Processes)

Run frontend and backend separately for development:

```bash
# Install all dependencies
npm run install:all

# Run both frontend and backend in development mode
npm run dev
```

This runs:
- Backend on `http://localhost:3001`
- Frontend on `http://localhost:5173` (or your Vite port)

## Production Mode (Single Process)

Serve both frontend and backend from a single Express server:

```bash
# Build the frontend
npm run build

# Start the production server (serves both frontend and backend)
npm start
```

The app will be available at `http://localhost:3001`

## Docker Deployment

### Option 1: Using Docker Compose (Recommended)

```bash
# Build and start the container
npm run docker:up

# View logs
npm run docker:logs

# Stop the container
npm run docker:down

# Rebuild and restart (after code changes)
npm run docker:rebuild
```

### Option 2: Using Docker Directly

```bash
# Build the image
npm run docker:build

# Run the container
npm run docker:run
```

### Manual Docker Commands

```bash
# Build the image
docker build -t sustainhub-webapp .

# Run the container
docker run -p 3001:3001 \
  -v $(pwd)/backend/fridge.db:/app/backend/fridge.db \
  sustainhub-webapp

# Run with docker-compose
docker-compose up -d

# View logs
docker-compose logs -f sustainhub

# Stop
docker-compose down
```

## Environment Variables

The backend uses the following environment variables:

- `NODE_ENV`: Set to `production` for production mode
- `PORT`: Server port (default: 3001)

## Database

The SQLite database (`fridge.db`) is:
- Created automatically on first run
- Persisted as a volume in Docker
- Located at `backend/fridge.db`

## API Endpoints

Once running, the API is available at:

- Health check: `http://localhost:3001/api/health`
- Ingredients: `http://localhost:3001/api/ingredients`
- Recipes: `http://localhost:3001/api/recipes`

## ESP32 Connection

Update your ESP32 code with the server IP:

```cpp
const char* serverUrl = "http://YOUR_SERVER_IP:3001/api";
```

For Docker deployment, use your host machine's IP address (not localhost).

## Ports

- **3001**: Main application port (both frontend and backend in production)
- **5173**: Frontend development server (dev mode only)

## Directory Structure

```
sustainhub_webapp/
├── backend/           # Express.js backend
│   ├── server.js      # Main server file
│   ├── fridge.db      # SQLite database
│   └── package.json
├── frontend/          # React frontend
│   ├── src/
│   ├── dist/          # Built files (production)
│   └── package.json
├── Dockerfile         # Docker build configuration
├── docker-compose.yml # Docker Compose configuration
└── package.json       # Root package file
```

## Troubleshooting

### Docker Issues

1. **Port already in use**: Stop other services on port 3001
   ```bash
   lsof -ti:3001 | xargs kill -9
   ```

2. **Database not persisting**: Ensure the volume mount is correct in docker-compose.yml

3. **Cannot connect to API**: Check that firewall allows port 3001

### Production Mode Issues

1. **Frontend not loading**: Ensure you ran `npm run build` first
2. **API routes not working**: Check that API routes are defined before the catch-all route in server.js
